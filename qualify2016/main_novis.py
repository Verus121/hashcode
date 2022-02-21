from collections import defaultdict
from math import ceil, sqrt 

file = open("files/redundancy.in", "r")

file_data = []
for line in file:
    line = line[:-1] # why? 
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
# print("warehouse_datas:", warehouse_datas) # gives number of warehouses
print("n_orders:", n_orders)
# print("order_datas:", order_datas) # gives number of orders.

# get all items and put in list 
# product_shipping_list 
    # item1 : producttype (weight), current location, destination. 
    # item2 : producttype (weight), current location, destination. 
    # item3 : producttype (weight), current location, destination. 

# shipping_plan_list # list (of item data) of list (item id, start, end)
    # duck1-phoneA: lidcup
    # duck2-phoneB: unlidcup

# warehouse_items_unassigned_data

# for each customer in customers
    # create warehouse_sorted_by_distance_to_customer_list 
    # for each order_item in customer_orders
        # for each warehouse in warehouse_sorted_by_distance_to_customer_list
            # if item in warehouse and item has no end
                # update shipping_plan_list

# product, number of product exists in the universe.

for i in range (n_product_types):
    total = 0
    for warehouse_data in warehouse_datas:
        total += warehouse_data[1][i]
    # print("Product Type: ", i, " there exists ", total)

for i in range (n_product_types):
    total = 0
    for order_data in order_datas:
        for element in order_data[1]:
            if element == i:
                total += 1
    # print("Product Type: ", i, " was requested ", total)
    

### 
# get all items and put in list 
# product_shipping_list 
    # item1 : producttype (weight), current location, destination. 
    # item2 : producttype (weight), current location, destination. 
    # item3 : producttype (weight), current location, destination. 

# product_shipping_list = []
# for warehouse_data in warehouse_datas:
#     for i in range(len(warehouse_data[1])):
#         for j in range(warehouse_data[1][i]):
#             product_shipping_info = [i, warehouse_data[0]]
#             product_shipping_list.append(product_shipping_info)

# print(product_shipping_list)

### HUNTER CHANGE # 1:
### CHANGE PRODUCT_SHIPPING_LIST TO PRODUCT_SHIPPING_DICT
# get all items and put in dictionary
# proudct_shipping_dict
    # (item, ware_coordinate): number_of_such_item

product_shipping_dict=  defaultdict(int)
for warehouse_data in warehouse_datas:
    for i in range(len(warehouse_data[1])):
        item_cords_key = (i, tuple(warehouse_data[0]))
        product_shipping_dict[item_cords_key] = warehouse_data[1][i]



# for each customer in customers
    # create warehouse_sorted_by_distance_to_customer_list 
    # for each order_item in customer_orders
        # for each warehouse in warehouse_sorted_by_distance_to_customer_list
            # if item in warehouse and item has no end
                # update shipping_plan_list

# for order in order_datas:
#     warehouse_sorted_by_distance_to_customer_list = sorted(warehouse_datas, key=lambda x: ((x[0][0] - order[0][0])**2 + (x[0][1] - order[0][1])**2))
#     # print(order[0], [x[0] for x in warehouse_sorted_by_distance_to_customer_list])
#     for item in order[1]:
#         for warehouse in warehouse_sorted_by_distance_to_customer_list:
#             ware_coordinate = warehouse[0]
#             product_info = [item, ware_coordinate]
#             for product_shipping_info in product_shipping_list:
#                 if product_info == product_shipping_info:
#                     product_shipping_info.append(order[0])
#                     break

# for product_shipping_item in product_shipping_list:
#     if len(product_shipping_item) == 2:
#         product_shipping_list.remove(product_shipping_item)

# product_shipping_list = [x for x in product_shipping_list if len(x) == 3]

### HUNTER CHANGE 2
### make the above loop more efficient with product_shipping_dict

new_product_shipping_list = []
for order in order_datas:
    warehouse_sorted_by_distance_to_customer_list = sorted(warehouse_datas, key=lambda x: ((x[0][0] - order[0][0])**2 + (x[0][1] - order[0][1])**2))
    # print(order[0], [x[0] for x in warehouse_sorted_by_distance_to_customer_list])
    for item in order[1]:
        for warehouse in warehouse_sorted_by_distance_to_customer_list:
            ware_coordinate = warehouse[0]
            product_info = (item, tuple(ware_coordinate))
            if (product_info in product_shipping_dict) and (product_shipping_dict[product_info] > 0):
                new_product_shipping_list.append([item, ware_coordinate, order[0]])
                product_shipping_dict[product_info] -= 1
                break

product_shipping_list = new_product_shipping_list
# print("start")
# for product_shipping_item in product_shipping_list:
#     print(product_shipping_item)

# divide product shipping list into n_drones 
list_of_product_shipping_lists = []
for _ in range(n_drones):
    list_of_product_shipping_lists.append([])

# droneiter = 0
for i in range(len(product_shipping_list)):
    droneid = (i % n_drones)
    list_of_product_shipping_lists[droneid].append(product_shipping_list[i])

# print("hi")
# for drone_todos in list_of_product_shipping_lists:
#     print(drone_todos)
    


# for product_shipping_item in product_shipping_list:
#     droneboy = n_drones
#     droneiter = 0
#     for i in range(n_drones):
#         if 

# list of where drone is
    # where it is, what it is doing, 
    # T0 0~0 L 
    # T1 1~0 F 
    # T2 2~0 F
    # T3 2~1 F
    # T4 2~1 U
    # T5 2~0 F 

# list of drone instructions
    # list of droneid instructions
        # 0~0
        # L itemid 0~0
        # U itemid 2~0
        # L itemid 0~0
        # U itemid 4~2

# drone 
    # for all orders
        # order - create drone instructiosn for order 

drones_instructions_list = []
for _ in range(n_drones):
    drones_instructions_list.append([])

for droneid, droneid_instructions_list in enumerate(drones_instructions_list):
    # drone0_instructions_list = []
    # add current position of drone to beginnign of drone0 isntructions list 
    drone_start = warehouse_datas[0][0]
    droneid_instructions_list.append([drone_start])

    for product in list_of_product_shipping_lists[droneid]:
        product_location = product[1]
        if droneid_instructions_list[-1][-1] != product_location:
            droneid_instructions_list.append(['F', None, droneid_instructions_list[-1][-1], product_location])
        droneid_instructions_list.append(['L', product[0], product_location])
        droneid_instructions_list.append(['F', product[0], droneid_instructions_list[-1][-1], product[2]]) # end 
        droneid_instructions_list.append(['U', product[0], product[2]]) # end 

# print("\n\n\n")
# for i, droneid_instructions_list in enumerate(drones_instructions_list):
#     print("Instructions for drone", i)
#     for instruction in droneid_instructions_list:
#         print(instruction)

    # if drone one not at product start
        # drone one to product start
    # load product 
    # deliver to end 

# time = 0
# for isntruction in drone0 instruct list
    # if len(instruct) == 1
        # continue
    # if inst[0] in ["L", "U"]:
        # time += 1
    # if inst[0] == "F"
        # start_pos = inst[2]
        # end_pos = inst[3]
        # euclidDist = func(start, end)
        # time += ceil(eucliddist)

for droneid, droneid_instructions_list in enumerate(drones_instructions_list):
    time = 0
    for step in droneid_instructions_list:
        if len(step) == 1:
            continue
        if step[0] in ["L", "U"]:
            time += 1
        if step[0] == "F":
            start = step[2]
            end = step[3]
            euclidDist = sqrt((start[0] - end[0])**2 + (start[1] - end[1])**2)
            time += ceil(euclidDist)
    print(f"time for drone {droneid} to deliver: {time}")

# print("drone delivery time: ", time)
print("simul time: ", n_turns)
