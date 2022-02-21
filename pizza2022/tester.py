

# likes_set = {'a', 'b', 'c'}
# dislikes_set = {'e','f','g'}
# client_preferences_tuple = (likes_set, dislikes_set)
# pizza_set = {'a', 'b', 'c', 'x', 'y', 'z'}

def client_eats_pizza(pizza_set, client_preferences_tuple):
    likes_set, dislikes_set = client_preferences_tuple
    if dislikes_set.intersection(pizza_set) or not likes_set.issubset(pizza_set):
        return 0
    else:
        return 1

def get_client_index(i):
    if i % 2 == 0:
        index = int(i/2)
    else:
        index = int((i-1)/2)
    return index # 1,2 -> 1 and 3,4 -> 2, etc.

# returns clients_array_of_client_preferences_tuples, an array of tuples, each containing two preference sets from the same customer.
# returns global_ingredients_set, set of all ingredients, prefered and not prefered. 
def process_file(in_file):
    file = open(in_file, "r")
    customers = int(file.readline())

    clients_array_of_client_preferences_tuples = [tuple() for customer in range(customers)]
    global_ingredients_set = set()

    for i, line in enumerate(file):
        # print(line) = numberofingredients ingredientname1 ingredientname2 ingredientname3
        ingredients_array = line.split() # ['numberofingredients', 'ingredientname1', 'ingredientname2', 'ingredientname3']
        ingredients_array_clean = ingredients_array.pop(0) # don't need number. ['ingredientname1', 'ingredientname2', 'ingredientname3']
        ingredients_set = set(ingredients_array_clean) # ('ingredientname1', 'ingredientname2', 'ingredientname3')
        
        clients_array_of_client_preferences_tuples[get_client_index(i)].append(ingredients_set) # tuples are unchangable. so. 

        global_ingredients_set.update(ingredients_set)

    file.close()
    return clients_array_of_client_preferences_tuples, global_ingredients_set

def new_process_file(input_file):
    file = open(input_file, "r")
    customers = file.readline()

    raw_customer_lines = []
    for line in file:
        raw_customer_lines.append(line)
    
    return customers, raw_customer_lines


def get_clean_customer_lines(raw_customer_lines):
    clean_customer_lines = []
    for raw_customer_line in raw_customer_lines:
        raw_customer_list = raw_customer_line.split()
        raw_customer_list.pop(0)
        clean_customer_lines.append(raw_customer_list)
    return clean_customer_lines

def clean_customer_data(raw_customer_lines):
    clean_customer_lines = get_clean_customer_lines(raw_customer_lines)
    customer_likes_data = clean_customer_lines[::2]
    customer_dislikes_data = clean_customer_lines[1::2]

    customer_data = []
    for i in range(0, len(customer_likes_data)):
        customer_data.append([customer_likes_data[i], customer_dislikes_data[i]])
    return customer_data

def pizza(input_file):
    # preferences, ingredients = process_file(input_file)
    customers, raw_customer_lines = new_process_file(input_file)
    print(customers)
    customer_data = clean_customer_data(raw_customer_lines)
    print(len(customer_data))

pizza("files/d.txt") # "files/od.txt"