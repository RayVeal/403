import sys
import tkinter as tk
import random

class CustomCanvas:
    def __init__(self, height, width, background_color="white"):
        self.root = tk.Tk()
        self.canvas = tk.Canvas(self.root, height=height, width=width, bg=background_color)
        self.canvas.pack()

class Rectangle:
    def __init__(self, properties):
        self.properties = properties

def is_overlap(rect1, rect2):
    return (
        rect1.properties['x'] < rect2.properties['x'] + rect2.properties['width'] and
        rect1.properties['x'] + rect1.properties['width'] > rect2.properties['x'] and
        rect1.properties['y'] < rect2.properties['y'] + rect2.properties['height'] and
        rect1.properties['y'] + rect1.properties['height'] > rect2.properties['y']
    )

def pack(backtrack, rectangles, canvas_size):
    if backtrack == len(rectangles):
        return True  # All rectangles are placed successfully

    for y in range(canvas_size[1]):
        for x in range(canvas_size[0]):
            rectangles[backtrack].properties['x'] = x
            rectangles[backtrack].properties['y'] = y

            # Check for overlap with previously placed rectangles
            overlap = any(is_overlap(rectangles[backtrack], r) for r in rectangles[:backtrack])

            if not overlap and pack(backtrack + 1, rectangles, canvas_size):
                return True  # Successful placement for this rectangle, proceed to the next one

    return False  # Unable to find a valid placement for this rectangle

def main(file_path):
    try:
        with open(file_path, 'r') as file:
            canvas_size = tuple(map(int, file.readline().strip().split(',')))
            rectangles = [Rectangle(dict(zip(['height', 'width'], map(int, line.strip().split(','))))) for line in file]
    except FileNotFoundError:
        print(f"File not found: {file_path}")
        return
    except Exception as e:
        print(f"Error reading file: {e}")
        return

    custom_canvas = CustomCanvas(*canvas_size, background_color="lightgray")

    if pack(0, rectangles, canvas_size):
        for rect in rectangles:
            custom_canvas.canvas.create_rectangle(
                rect.properties['x'], rect.properties['y'],
                rect.properties['x'] + rect.properties['width'], rect.properties['y'] + rect.properties['height'],
                outline="black", fill="blue"
            )
    else:
        print("Unable to find a valid placement for all rectangles.")

    custom_canvas.root.mainloop()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python Assignment7.py <file_path>")
    else:
        main(sys.argv[1])