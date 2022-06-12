import pygame
import math
import test_map
import map_parser



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


screen_height, screen_width = test_map.map_height, test_map.map_width
example_path_1 = [((3*i, 500), (0, i)) for i in range(screen_width)]
example_path_2 = [((screen_width-10*i, 500), (0, -i)) for i in range(screen_width)]

def main():
    pygame.init()
    win = pygame.display.set_mode((screen_height, screen_width))
    pygame.display.set_caption("Traffic Sim")


    fps = 50 
    clock = pygame.time.Clock()  
    car1 = Car(100, 100, "basic_car.png")
    car2 = Car(500, 500, "basic_car.png")

    running = True
    i = 0
    while running:
        # set fps  
        clock.tick(fps)  
        # Check to see if we are trying to close the window
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
                
        win.fill((255, 255, 255))

        # Initialize map 
        map_parser.draw_map(win)
        # road0_width = test_map.bottom_right0[0] - test_map.top_left0[0]
        # road0_height = test_map.top_left0[1] - test_map.bottom_right0[1]
        # # pygame.draw.rect(win, road_color,
        #                  pygame.Rect(test_map.top_left0,
        #                              (road0_width, road0_height)))

        # if car.x < 500:
        #     car.x += 5
        # if car.angle > 0:
        #     car.angle -= 2
        # else:
        #     car.y = (car.y + 10) % screen_height
        v1 = example_path_1[i][1]
        p1 = example_path_1[i][0]
        car1.angle = bearing((0, 0), v1) - 90
        car1.x, car1.y = p1[0], p1[1]
        draw(car1.image, car1.x, car1.y, car1.angle, win)

        v2 = example_path_2[i][1]
        p2 = example_path_2[i][0]
        car2.angle = bearing((0, 0), v2) - 90
        # car2.angle = 135.0
        car2.x, car2.y = p2[0], p2[1]
        draw(car2.image, car2.x, car2.y, car2.angle, win)


        i += 1
        pygame.display.update()

    pygame.quit()


if __name__ == "__main__":
    main()

        
# Player rectangle
# pygame.draw.rect(win, (255, 0, 0), (x, y, width, height))

# Boundaries
# pygame.draw.rect(win, (0, 0, 0), (0, 0, 850, 500))
# pygame.draw.rect(win, (0, 0, 0), (screen_width-850, 0, 850, 500))
# pygame.draw.rect(win, (0, 0, 0), (0, screen_height-500, 850, 500))
# pygame.draw.rect(win, (0, 0, 0), (screen_width-850, screen_height-500, 850, 500))

# t = pygame.time.get_ticks()
# for i in range(5):
#     pygame.draw.rect(win, ((i*50)%255, 0, 0), (900, (i*200 + t)%1920, width, height))
# # Store keys pressed
# keys = pygame.key.get_pressed()
# # Left arrow key is pressed
# if keys[pygame.K_LEFT] and x > 0:
#     # decrement in x co-ordinate
#     x -= vel
# # Right arrow key is pressed
# if keys[pygame.K_RIGHT] and x < screen_width - width:
#     # increment in x co-ordinate
#     x += vel
# # Up arrow key
# if keys[pygame.K_UP] and y > 0:
#     y -= vel
# # Down arrow key
# if keys[pygame.K_DOWN] and y < screen_height - width:
#     y += vel
    
