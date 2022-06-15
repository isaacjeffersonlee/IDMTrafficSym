import pygame
import math
import parser
import pandas as pd


def bearing(a: tuple, b: tuple) -> float:
    """Return the bearing in degrees of the vector from a to b."""
    dy, dx = b[1] - a[1], b[0] - a[0]
    return ((math.atan2(dy, dx) * (180/math.pi)) - 90.0) % 360.0


class Car(pygame.sprite.Sprite):
    def __init__(self, x: float, y: float,
                 image_path: str):
        super().__init__()
        self.x = x
        self.y = y
        self.image = pygame.image.load(image_path)
        self.rect = self.image.get_rect(center=(self.x, self.y))
        self.width, self.length = self.image.get_size()
        self.angle = 0.0


def draw(image, x, y, angle, window):
    """Perform any transforms to the image and draw it on the window."""
    # x += 15
    # y -= 15
    # rect = image.get_rect()  # Get outline rectangle
    # rect.center = (x, y)  # Center rectangle
    angle = angle % 360  # Prevent overflow
    rotated_image = pygame.transform.rotate(image, angle)
    rotated_rectangle = rotated_image.get_rect()
    rotated_rectangle.center = (x, y)
    window.blit(rotated_image, rotated_rectangle)


screen_height, screen_width = 1000, 1000
# example_path_1 = [((3*i, 500), (0, i)) for i in range(screen_width)]
# example_path_2 = [((screen_width-10*i, 500), (0, -i)) for i in range(screen_width)]


def main():
    pygame.init()
    win = pygame.display.set_mode((screen_height, screen_width))
    pygame.display.set_caption("Traffic Sim")

    fps = 50
    clock = pygame.time.Clock()

    # Initialize Car objects
    car1 = Car(100, 100, "basic_car.png")
    car2 = Car(500, 500, "basic_car.png")
    # Read in car path data
    car_paths = parser.get_car_paths_from_csv("car_data.csv")

    # Read in road data
    road_data_df = pd.read_csv("road_data.csv", sep=';')

    running = True
    i = 0
    sim_time = 60  # Simulation time in seconds
    dt = 1/fps  # Number of seconds that pass between frames
    t = 0
    while running:
        # Set fps
        clock.tick(fps)
        t += dt
        if t >= sim_time:
            break
        # Check to see if we are trying to close the window
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
        win.fill((255, 255, 255))

        # Draw the map map
        parser.draw_map_from_csv(win, road_data_df)

        #
        p1 = car_paths[0][i][0]
        d1 = car_paths[0][i][1]
        car1.angle = bearing((0, 0), d1)
        car1.x, car1.y = p1[0], p1[1]
        draw(car1.image, car1.x, car1.y, car1.angle, win)

        p2 = car_paths[1][i][0]
        d2 = car_paths[1][i][1]
        car2.angle = bearing((0, 0), d2)
        car2.x, car2.y = p2[0], p2[1]
        draw(car2.image, car2.x, car2.y, car2.angle, win)

        i += 1
        pygame.display.update()

    print("Simulation Complete!")
    pygame.quit()


if __name__ == "__main__":
    main()
