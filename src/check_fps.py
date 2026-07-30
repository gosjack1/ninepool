#!/usr/bin/env python3
"""
量測 RealSense RGB 影像串流的實際 fps 與 jitter。
用 header.stamp(相機擷取時間)而非本地接收時間,排除 ROS 傳輸延遲造成的誤差。

用法:
    python3 check_fps.py
    python3 check_fps.py --topic /camera/camera/color/image_raw --count 200
"""
import argparse
import numpy as np
import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy, DurabilityPolicy
from sensor_msgs.msg import Image


class FpsChecker(Node):
    def __init__(self, topic: str, count: int):
        super().__init__('fps_checker')
        self.count = count
        qos = QoSProfile(
            reliability=ReliabilityPolicy.RELIABLE,
            history=HistoryPolicy.KEEP_LAST,
            depth=1,
            durability=DurabilityPolicy.VOLATILE,
        )
        self.sub = self.create_subscription(Image, topic, self.cb, qos)
        self.stamps = []
        self.get_logger().info(f'Subscribing to {topic}, waiting for {count} frames...')

    def cb(self, msg: Image):
        t = msg.header.stamp.sec + msg.header.stamp.nanosec * 1e-9
        self.stamps.append(t)
        if len(self.stamps) >= self.count:
            dt = np.diff(self.stamps)
            print('\n=== FPS Measurement Result ===')
            print(f'frames collected : {len(self.stamps)}')
            print(f'mean fps         : {1 / np.mean(dt):.2f}')
            print(f'mean dt          : {np.mean(dt) * 1000:.3f} ms')
            print(f'std dt (jitter)  : {np.std(dt) * 1000:.3f} ms')
            print(f'max dt           : {np.max(dt) * 1000:.3f} ms')
            print(f'min dt           : {np.min(dt) * 1000:.3f} ms')
            print('================================\n')
            rclpy.shutdown()


def main():
    parser = argparse.ArgumentParser(description='RealSense RGB fps/jitter checker')
    parser.add_argument('--topic', type=str, default='/camera/camera/color/image_raw',
                         help='Image topic to subscribe to')
    parser.add_argument('--count', type=int, default=200,
                         help='Number of frames to collect before reporting')
    args = parser.parse_args()

    rclpy.init()
    node = FpsChecker(args.topic, args.count)
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()


if __name__ == '__main__':
    main()
