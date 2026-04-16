import subprocess
import sys

try:
    subprocess.Popen(["flatpak", "run", "org.DolphinEmu.dolphin-emu", "--exec", sys.argv[1], "-b"])
except Exception as e:
    print(f"Error in trying to run boot.dol with Dolphin Emulator: {e}")