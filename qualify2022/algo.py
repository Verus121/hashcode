## for finding skill within available people
def find_skill(skill, required_level, people_skills, person_is_working, assigned_people):
    for person in people_skills:
        if person_is_working[person]:
            continue
        else:
            if people_skills[person][skill] >= required_level:
                assigned_people[person] = (skill, required_level, people_skills[person][skill])
                return True
            if people_skills[person][skill] == required_level - 1:
                for assigned_person in assigned_people:
                    if assigned_people[assigned_person] >= required_level:
                        assigned_people[person] = (skill, required_level, people_skills[person][skill])
                        return True
    return False

def find_project(project, people_skills, person_is_working, project_skills, project_assignment):
    # dictionary: {person: (skill, required_level, current_level_of_person)}
    assigned_people = {}
    for skill in project_skills[project]:
        required_level = project_skills[project][skill]
        if not(find_skill(skill, required_level, people_skills, person_is_working, assigned_people)):
            return False
    project_assignment[project] = assigned_people
    return True


# janky greedy solution
# people_skills: {person: {skill: level}}
# person_is_working: {person: is_working/not_is_working}
# project_info {project_name: (information in the input thingy)}
# project_is_working {project_name: [is_working, days_till_completion]}
def solve_day(people_skills, person_is_working, project_skills, project_info, project_is_working, project_assignment):
    for project in project_skills:
        if project_is_working[project][0]:
            continue
        else:
            if find_project(project, people_skills, person_is_working, project_skills, project_assignment):
                project_is_working[project] = [True, project_info[0]]

def solve(people_skills, person_is_working, project_info, project_skills):
    time = 0
    score = 0
    project_is_working = {}
    project_assignment = {}
    for project in project_info:
        project_is_working[project] = [False, -1]
    while len(project_info) > 0:
        solve_day(people_skills, person_is_working, project_skills, project_is_working, project_assignment)

        for project in project_is_working:
            if project_is_working[project][0]:
                project_is_working[project][1] -= 1
                if project_is_working[project][1] == 0:
                    score += max(project_info[project][1] - (max(time - project_info[1], 0)), 0)
                    for person in project_assignment[project]:
                        people_skills[person][project_assignment[project][person][0]] = project_assignment[project][person][1]
        time +=1
    return (score)
                

    
    










                            
