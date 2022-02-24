## for finding skill (with the appropriate level) within available people
def find_skill_level(skill, required_level, people_skills, person_is_working, assigned_people):
    for person in people_skills:
        if person_is_working[person]:
            continue
        else:
            if people_skills[person][skill] >= required_level:
                assigned_people[person] = (skill, required_level, people_skills[person][skill])
                return True
            if people_skills[person][skill] == required_level - 1:
                for assigned_person in assigned_people:
                    if people_skills[assigned_person][skill] >= required_level:
                        assigned_people[person] = (skill, required_level, people_skills[person][skill])
                        return True
    return False

def find_project(project, people_skills, person_is_working, project_skills, project_assignment):
    # dictionary: {person: (skill, required_level, current_level_of_person)}
    assigned_people = {}
    for skill in project_skills[project]:
        for required_level in project_skills[project][skill]:
            if not(find_skill_level(skill, required_level, people_skills, person_is_working, assigned_people)):
                return False

    project_assignment[project] = assigned_people
    for person in project_assignment[project]:
        person_is_working[person] = True
    return True


# janky greedy solution
# people_skills: {person: {skill: level}}
# person_is_working: {person: is_working/not_is_working}
# project_info {project_name: (information in the input thingy)}
# project_is_working {project_name: [is_working, days_till_completion]}
def solve_day(people_skills, person_is_working, project_skills, project_info, project_is_working, project_assignment, output_string):
    for project in project_skills:
        if project_is_working[project][0]:
            continue
        else:
            if find_project(project, people_skills, person_is_working, project_skills, project_assignment):
                project_is_working[project] = [True, project_info[project][0]]
                output_string += f"{project}\n"
                people_string = ""
                for person in project_assignment[project]:
                    people_string += f"{person} "
                people_string = people_string[:-1]
                output_string += f"{people_string}\n"
    return output_string

def solve_day_sorted_by_time(people_skills, person_is_working, project_skills, project_info, project_is_working, project_assignment, output_string):
    project_list = []
    for project in project_skills:
        project_list.append(project)
    project_list = sorted(project_list, key = lambda x: project_info[x][2])
    for project in project_list:
        if project_is_working[project][0]:
            continue
        else:
            if find_project(project, people_skills, person_is_working, project_skills, project_assignment):
                project_is_working[project] = [True, project_info[project][0]]

def solve(people_skills, project_info, project_skills):
    time = 0
    score = 0
    project_is_working = {}
    project_assignment = {}
    person_is_working = {}
    for person in people_skills:
        person_is_working[person] = False
    done_project = set()
    assigned_projects = 0
    output_string = ""
    for project in project_info:
        project_is_working[project] = [False, -1]

    while len(done_project) < len(project_info):
        output_string = solve_day(people_skills, person_is_working, project_skills, project_info, project_is_working, project_assignment, output_string)
        for project in project_is_working:
            if project in done_project:
                continue
            if project_is_working[project][0]:
                project_is_working[project][1] -= 1
                if project_is_working[project][1] == 0:
                    score += max(project_info[project][1] - (max(time + 1 - project_info[project][2], 0)), 0)
                    for person in project_assignment[project]:
                        if people_skills[person][project_assignment[project][person][0]] <= project_assignment[project][person][1]:
                            people_skills[person][project_assignment[project][person][0]] +=1
                        person_is_working[person] = False
                    done_project.add(project)
                    del project_assignment[project]
                    assigned_projects+=1
        time +=1
    print(f"score:{score}")
    output_string = f"{assigned_projects}\n{output_string[:-1]}"
    # print(f"output:\n{output_string}")
    return output_string












                            
