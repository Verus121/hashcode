from collections import defaultdict

class SimulationData:
    def __init__(self, file_name):
        file = open(file_name, "r")
        file_data = []
        for line in file:
            file_data.append([val for val in line.split()])  

        self.number_of_contributors, self.number_of_projects = [int(val) for val in file_data[0]]

#######################################################################################################################
        # Contributors 
        current_line = 1

        self.contributor_to_skills_dict = {}

        for i in range(self.number_of_contributors):
            contributor_name = file_data[current_line][0]

            contributor_number_of_skills = int(file_data[current_line][1])

            name_to_level_dict = defaultdict(int)
            for j in range(contributor_number_of_skills): # fill name_to_level_dict
                skill = file_data[current_line+j+1]
                skill_name = skill[0]
                skill_level = int(skill[1])
                name_to_level_dict[skill_name] = skill_level

            self.contributor_to_skills_dict[contributor_name] = name_to_level_dict # fill contributor_to_skills_dict

            # Go to Next Contributor
            current_line += contributor_number_of_skills + 1

#######################################################################################################################
        # Projects 
        current_line = current_line

        # self.projects = "Hi Projects"
        self.projects_info_dict = {} 
        self.projects_skills_dict = {}
    
        for i in range(self.number_of_projects):
            project_name = file_data[current_line][0]

            # project_info
            project_info = tuple([int(val) for val in file_data[current_line][1:]])
            self.projects_info_dict[project_name] = project_info # fill projects_info_dict

            # project_skills
            project_number_of_skills = project_info[-1]

            # name_to_level_dict = {}
            name_to_level_dict = defaultdict(list)

            for j in range(project_number_of_skills): # fill name_to_level_dict
                skill = file_data[current_line+j+1]
                skill_name = skill[0]
                skill_level = int(skill[1])
                # name_to_level_dict[skill_name] = skill_level
                name_to_level_dict[skill_name].append(skill_level)
                name_to_level_dict[skill_name] = sorted(name_to_level_dict[skill_name], reverse=True)


            self.projects_skills_dict[project_name] = name_to_level_dict # fill projects_skills_dict
        
            # Go to Next Project Line
            current_line += project_number_of_skills + 1


    def print_info(self):
        print("Number of Contributors:", self.number_of_contributors, "Number of Projects:", self.number_of_projects)
        print("Contributors:", self.contributor_to_skills_dict)
        print("Project Info:", self.projects_info_dict)
        print("Project Skills:", self.projects_skills_dict)