from hiwin_control.config_utils import resolve_config_path


def test_resolve_config_path_returns_existing_file():
    path = resolve_config_path("arm.yaml")

    assert path.is_file()
    assert path.name == "arm.yaml"
