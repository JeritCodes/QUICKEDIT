from PIL import Image, ImageDraw, ImageFont
import os

def ascii_to_png(font_path, output_dir, font_size=32, font_color=(0, 0, 0), bg_color=(255, 255, 255)):

    try:
        font = ImageFont.truetype(font_path, font_size)
    except IOError:
        print(f"Error: Could not load font from {font_path}")
        return

    os.makedirs(output_dir, exist_ok=True)

    for char_code in range(33, 127):
        char = chr(char_code)

        #More robust width/height/offset calculation:
        left, top, right, bottom = font.getbbox(char)


        width = right - left

        height = bottom - top




        #Fixes offset rendering problems that happen for some fonts


        offset_x, offset_y = font.getoffset(char)



        image = Image.new("RGBA", (width + 2, height + 2), bg_color)  # Padding to handle edges


        draw = ImageDraw.Draw(image)

        try:
            draw.text((-offset_x, -offset_y), char, font=font, fill=font_color)


            image.save(os.path.join(output_dir, f"{char_code}.png"))
        except Exception as e:
            print(f"Error saving image: {e}")




ascii_to_png("VCR_OSD_MONO_1.001.ttf", "output_images", font_size=42)  #Larger font
