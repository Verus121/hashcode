from random import randrange, sample
RANDOMTIMES = 1000
SAMPLENUMBERLOW = 0
ADJUSTSAMPLENUMBERTOP = 1 # 1 is full range


# given pizza, client_preference
# return 1 if will come, 0 if wont. 
# pizza is set of ingredients.
# 

# client_preferences[likes_set, dislikes_set]
#  
# client_preference
# pizza_meets_client_preferences(pizza, client_preference)
#  

def score_answer(answer, preferences): 
    score = 0
    for pref in preferences:
        like = set(pref[0])
        dislike = set(pref[1])
        if not (dislike & answer) and like.issubset(answer):
            score += 1
    return score

def output_answer(out_file, best_answer):
    file = open(out_file, "w")
    file.write(str(len(best_answer)))
    for ingredient in best_answer:
        file.write(" " + ingredient)
    file.close()

def generate_answer(preferences, toppings):
    highscore = 0
    best_answer = []

    for i in range(RANDOMTIMES):
        sample_number = randrange(SAMPLENUMBERLOW, len(toppings)+ADJUSTSAMPLENUMBERTOP) # replace 1 with the least amount of liked toppings
        answer = sample(toppings, sample_number)

        new_score = score_answer(set(answer), preferences)
        if new_score > highscore:
            highscore = new_score
            best_answer = answer

    return highscore, best_answer
    
def to_index(i):
    if i % 2 == 0:
        index = int(i/2)
    else:
        index = int((i-1)/2)
    return index # 1,2 -> 1 and 3,4 -> 2, etc.

def process_file(in_file):
    file = open(in_file, "r")
    customers = int(file.readline())
    preferences = [[] for customer in range(customers)]
    toppings = set()
    for i, line in enumerate(file):
        line = line.split()
        line.pop(0) # don't need number.
        toppings.update(line)
        preferences[to_index(i)].append(tuple(line))
    file.close()
    return preferences, toppings





def pizza(in_file, out_file):
    preferences, toppings = process_file(in_file)
    # print(len(toppings))
    highscore, best_answer = generate_answer(preferences, toppings)
    output_answer(out_file, best_answer)
    print(highscore)

# pizza("files/a.txt", "files/oa.txt")
# pizza("files/b.txt", "files/ob.txt")
# pizza("files/c.txt", "files/oc.txt")
pizza("files/d.txt", "files/od.txt")
# pizza("files/e.txt", "files/oe.txt")
