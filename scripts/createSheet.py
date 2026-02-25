from pathlib import Path
import os

directory_path = Path('../sheets/heart/')
output_file = f'{directory_path.resolve()}/sheet.t3s'

t3xPath = Path(f'../romfs/gfx')

#os.system("convert ../assets/herochar/herochar_spritesheet.png -crop 16x16 +repage ../sheets/player_sheet/image_%d.png")

files = sorted(
    [f.name for f in directory_path.iterdir() if f.is_file() and f.suffix == '.png'],
    key=lambda x: int(''.join(filter(str.isdigit, x)) or 0)
)

with open(output_file, 'w') as f:
    f.write("--atlas -f rgba8888 -z auto\n")
    for filename in files:
        f.write(f"{filename}\n")

print(f"Successfully wrote {len(files)} filenames to {output_file}")

os.system(f'tex3ds -i {directory_path}/sheet.t3s -o {t3xPath}/{directory_path.name}.t3x')