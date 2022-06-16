import pygame
import pandas as pd
import numpy as np


def draw_map_from_csv(pygame_window, df):
    for idx, row in df.iterrows():  # Loop over rows
        road_color = ((220 - 50*idx) % 255, (220 - 50*idx) %
                      255, (220 - 50*idx) % 255)
        top_left = eval(row["topLeft"])
        road_width = eval(row["bottomRight"])[0] - eval(row["topLeft"])[0]
        road_height = eval(row["bottomRight"])[1] - eval(row["topLeft"])[1]
        pygame.draw.rect(pygame_window, road_color,
                         pygame.Rect(top_left, (road_width, road_height)))


def get_car_paths_from_csv(car_csv_file):
    """Return nested lists for each car, corresponding to direction
    and position for each time interval."""
    df = pd.read_csv(car_csv_file, sep=';', header=None)
    df.drop(columns=df.columns[-1], axis=1,
            inplace=True)  # Remove the last col
    car_paths = []
    for car_num, values in df.iteritems():
        car_path = []
        for val in values:
            str_list = val.split(',')
            car_path.append(((float(str_list[0]), float(str_list[1])), float(str_list[2])))
        car_paths.append(car_path)

    return car_paths


if __name__ == "__main__":
    # get_car_paths_from_csv("car_data.csv")
    draw_map_from_csv(0, "road_data.csv")
