import pandas as pd


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

def get_light_coords_from_csv(lights_csv_file):
    df = pd.read_csv(lights_csv_file, sep=';', header=None)
    df.drop(columns=df.columns[-1], axis=1,
            inplace=True)  # Remove the last col
    all_road_sources = []
    all_road_sinks = []
    for road_num, values in df.iteritems():
        road_sources = []
        road_sinks = []
        for val in values:
            str_list = val.split(',')
            road_sources.append((int(str_list[0]), int(str_list[1])))
            road_sinks.append((int(str_list[2]), int(str_list[3])))
        all_road_sources.append(road_sources)
        all_road_sinks.append(road_sinks)

    return all_road_sources, all_road_sinks

if __name__ == "__main__":
    # get_car_paths_from_csv("car_data.csv")
    # draw_map_from_csv(0, "road_data.csv")
    sources, sinks = get_light_coords_from_csv("data/light_data.csv")
    print(sources[0])
