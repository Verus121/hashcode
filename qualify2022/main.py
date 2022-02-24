import input
from algo import solve

a_file = "files/a_an_example.in.txt"
b_file = "files/b_better_start_small.in.txt"
c_file = "files/c_collaboration.in.txt"
d_file = "files/d_dense_schedule.in.txt"
e_file = "files/e_exceptional_skills.in.txt"
f_file = "files/f_find_great_mentors.in.txt"

file = b_file

sim = input.SimulationData(file)
sim.print_info()

output = solve(sim.contributor_to_skills_dict, sim.projects_info_dict, sim.projects_skills_dict)




