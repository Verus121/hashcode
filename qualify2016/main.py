# Project - https://storage.googleapis.com/coding-competitions.appspot.com/HC/2016/hashcode2016_qualification_task.pdf
# See Open CV for graphing
# Work on single drone algorithm. 

import matplotlib.pyplot as plt
import numpy as np

file = open("files/test.in", "r")

file_data = []
for line in file:
    line = line[:-1]
    file_data.append(line)

n_rows, n_columns, n_drones, n_turns, max_weight_of_drone = tuple([int(val) for val in file_data[0].split()])

n_product_types = int(file_data[1])

product_weights = [int(val) for val in file_data[2].split()]

n_warehouses = int(file_data[3])

warehouse_data_start_index = 4
warehouse_data_end_index = warehouse_data_start_index + (n_warehouses * 2) - 1
warehouse_datas = []
for i in range(warehouse_data_start_index, warehouse_data_end_index+1, 2):
    j = i
    k = i+1
    warehouse_coordinate = [int(val) for val in file_data[j].split()]
    warehouse_products_data_SPECIAL = [int(val) for val in file_data[k].split()]
    warehouse_datas.append((warehouse_coordinate, warehouse_products_data_SPECIAL))

n_orders = int(file_data[warehouse_data_end_index+1])

orders_data_start_index = warehouse_data_end_index+2
orders_data_end_index = orders_data_start_index + (n_orders * 3) - 1
order_datas = []
for i in range(orders_data_start_index, orders_data_end_index+1, 3):
    j = i
    # k = i+1 # NOT NEEDED
    l = i+2
    order_coordinate = [int(val) for val in file_data[j].split()]
    # n_order_items = int(file_data[k]) # NOT NEEDED
    order_productids = [int(val) for val in file_data[l].split()]
    order_datas.append((order_coordinate, order_productids))

# All data has been processed and stored from the file. 

print("n_rows:", n_rows, "\n" + "n_columns:", n_columns, "\n" + "n_drones:", n_drones, "\n" + "n_turns:", n_turns, "\n" + "max_weight_of_drone:", max_weight_of_drone)
print("n_product_types:", n_product_types) # better data structure for this? hashmap? not really needed.
print("product_weights:", product_weights) # gives product weights
print("n_warehouses:", n_warehouses)
print("warehouse_datas:", warehouse_datas) # gives number of warehouses
print("n_orders:", n_orders)
print("order_datas:", order_datas) # gives number of orders.






# data visualization

warehouse_order_map = np.zeros((n_rows, n_columns))

# print(warehouse_order_map)


# warehouse_locations = 
for warehouse_data in warehouse_datas:
    location, _ = warehouse_data
    x, y = location
    warehouse_order_map[x, y] = 1

# print(myarray)


# now matplot this array.   
for order_data in order_datas:
    location, _ = order_data
    x, y = location
    warehouse_order_map[x,y] = 2
 

plt.figure(figsize=(5,5))
plt.imshow(warehouse_order_map)
plt.show()

drone_map = np.zeros((n_rows, n_columns))
drone_initial_location = warehouse_datas[0][0]
drone_locations = np.array([drone_initial_location for _ in range(n_drones)])
for drone_location in drone_locations:
    x, y = drone_location
    drone_map[x, y] += 1

plt.figure(figsize=(5,5))
plt.imshow(drone_map, cmap="gray")
plt.colorbar()
plt.show()
