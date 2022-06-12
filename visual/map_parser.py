import pygame
import test_map

def draw_map(pygame_window):
    for i in range(test_map.road_number):
        road_color = ((220 - 50*i) % 255, (220 - 50*i) % 255, (220 - 50*i) % 255)
        # This is really dodgy
        # TODO: Implement a better method for saving these vals
        road_width = eval(f"test_map.bottom_right{i}[0] - test_map.top_left{i}[0]")
        road_height = eval(f"test_map.bottom_right{i}[1] - test_map.top_left{i}[1]")
        top_left = eval(f"test_map.top_left{i}") 
        # print(top_left, road_width, road_height)
        pygame.draw.rect(pygame_window, road_color,
                         pygame.Rect(top_left, (road_width, road_height)))
