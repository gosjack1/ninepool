from pathlib import Path


def resolve_config_path(filename: str) -> Path:
    """Resolve a config file relative to the package and workspace.

    This works both from the source tree and from an installed package.
    """
    package_dir = Path(__file__).resolve().parent

    candidates = [
        package_dir / filename,
        package_dir.parent / "hiwin_control" / filename,
        Path.cwd() / filename,
        Path.cwd() / "src" / "hiwin_control" / "hiwin_control" / filename,
    ]

    for candidate in candidates:
        if candidate.exists():
            return candidate

    return package_dir / filename
