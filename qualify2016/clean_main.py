from math import prod


class Coordinate:
    def __init__(self, row, col):
        self.row = row
        self.col = col
    
    def print(self):
        print("[", self.row, ",", self.col, "]")



# Main
file = open("files/test.in", "r")

file_data = []
for line in file:
    file_data.append([int(val) for val in line.split()])  
    # if line has 1 number, should it be in a list? 
# print(file_data) 

simulation_parameters = file_data[0]
map_rows, map_columns, number_of_drones, simulation_turns, max_weight_of_drone = simulation_parameters
# print(map_rows, map_columns, number_of_drones, simulation_turns, max_weight_of_drone)

number_of_product_types = file_data[1]
product_weights = file_data[2]
# print(number_of_product_types, product_weights)

number_of_warehouses = file_data[3][0] # see filedata extraction 
print(number_of_warehouses)
warehouse_data_start_index = 4
lines_per_warehouse = 2
warehouse_data_end_index = warehouse_data_start_index + (number_of_warehouses * lines_per_warehouse)
print(warehouse_data_start_index, warehouse_data_end_index)

# warehouse_datas = []
# for i in range(warehouse_data_start_index, warehouse_data_end_index+1, 2):
#     j = i
#     k = i+1
#     warehouse_coordinate = [int(val) for val in file_data[j].split()]
#     warehouse_products_availability = [int(val) for val in file_data[k].split()]
#     warehouse_datas.append((warehouse_coordinate, warehouse_products_availability))