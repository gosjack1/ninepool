import pooltool as pt
from pooltool.objects import PocketTableSpecs

table_specs = PocketTableSpecs(
    l=1.120, w=0.550,
    cushion_width=0.0288, cushion_height=0.02432,
    corner_pocket_width=0.065, corner_pocket_depth=0.0237,
    corner_pocket_radius=0.0352, corner_jaw_radius=0.0119,
    side_pocket_width=0.080, side_pocket_depth=0.0389,
    side_pocket_radius=0.0366, side_jaw_radius=0.0045,
)
table = pt.Table.from_table_specs(table_specs)
print(f"table.w (x範圍) = {table.w}, table.l (y範圍) = {table.l}")

# 桌子座標: x 軸沿 w (短邊), y 軸沿 l (長邊)
balls = {
    "cue": pt.Ball.create("cue", xy=(0.2, 0.3), R=0.019),
    "1":   pt.Ball.create("1", xy=(0.2, 0.7), R=0.019),
}
cue = pt.Cue(cue_ball_id="cue")
shot = pt.System(table=table, balls=balls, cue=cue)
shot.cue.set_state(V0=2.0, phi=pt.aim.at_ball(shot, "1"))
pt.simulate(shot, inplace=True)

print("事件數:", len(shot.events))
for e in shot.events:
    print(e.event_type.name, [a.id for a in e.agents])
