import pygame

def draw_image(pygame_window, image, x, y, angle):
    """Perform any transforms to the image and draw it on the window."""
    # x += 15
    # y -= 15
    # rect = image.get_rect()  # Get outline rectangle
    # rect.center = (x, y)  # Center rectangle
    rotated_image = pygame.transform.rotate(image, angle)
    rotated_rectangle = rotated_image.get_rect()
    rotated_rectangle.center = (x, y)
    pygame_window.blit(rotated_image, rotated_rectangle)

# TODO: Optimize this
def draw_map_from_df(pygame_window, df):
    for idx, row in df.iterrows():  # Loop over rows
        road_color = ((220 - 50*idx) % 255, (220 - 50*idx) %
                      255, (220 - 50*idx) % 255)
        top_left = eval(row["topLeft"])
        road_width = eval(row["bottomRight"])[0] - eval(row["topLeft"])[0]
        road_height = eval(row["bottomRight"])[1] - eval(row["topLeft"])[1]
        pygame.draw.rect(pygame_window, road_color,
                         pygame.Rect(top_left, (road_width, road_height)))

def draw_lights(pygame_window, idx, sources, sinks, sink_colour, source_colour):
    r = 5  # Radius of circles
    for road in sources:
        center = road[idx]
        pygame.draw.circle(pygame_window, source_colour, center, r)
    for road in sinks:
        center = road[idx]
        pygame.draw.circle(pygame_window, sink_colour, center, r)
