# SysmonDisable

Disable Sysmon (or any driver/service) by changing its registry `Start` value. The driver won't load on next reboot.

## Usage

```
SysmonDisable.exe [service_name] [start_value]
```

| Argument | Default | Description |
|----------|---------|-------------|
| `service_name` | `SysmonDrv` | Service name under `HKLM\SYSTEM\CurrentControlSet\Services\` |
| `start_value` | `3` | 0=Boot, 1=System, 2=Auto, 3=Manual, 4=Disabled |

### Examples

```
SysmonDisable.exe                      # Set SysmonDrv to Manual (3)
SysmonDisable.exe SysmonDrv 4          # Set SysmonDrv to Disabled
SysmonDisable.exe Sysmon64 4           # Disable Sysmon service
```

Requires **administrator privileges**. Reboot required for changes to take effect.

## Build

### Cross-compile from Linux (mingw-w64)

```bash
make
```

### Windows (MSVC Developer Command Prompt)

```cmd
cl /O2 main.c /Fe:SysmonDisable.exe advapi32.lib
```

## Disclaimer

This tool is provided for **authorized security testing and educational purposes only**. Use it only on systems you own or have explicit written permission to test. Unauthorized use against systems you do not own is illegal. The author assumes no liability for misuse.

## License

MIT — see [LICENSE](LICENSE)
