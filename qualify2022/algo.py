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

def find_project(project, people_skills, person_is_working, project_skills):
    # dictionary: {person: (skill, required_level, current_level_of_person)}
    assigned_people = {}
    for skill in project_skills[project]:
        required_level = project_skills[project][skill]
        if not(find_skill(skill, required_level, people_skills, person_is_working, assigned_people)):
            return False
    return True


# janky greedy solution
# people_skills: {person: {skill: level}}
# person_is_working: {person: is_working/not_is_working}
# project_info {project_name: (information in the input thingy)}
# project_is_working {project_name: is_working}
def solve(people_skills, person_is_working, project_skills, project_is_working):
    for project in project_skills:
        if project_is_working[project]:
            continue
        else:
            find_project(project, people_skills, person_is_working, project_skills)



                            
