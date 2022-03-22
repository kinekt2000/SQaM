splited_total = [14.158,12.526,26.200,0.811,0.200,20.958,63.168,35967.942,94.137,6228.505,19.605,89.905,3.605]

print("splited_total:", sum(splited_total))

splited_mod_total = [9.826,12.753,20.053,2.679,196.984,36.689,61.816,21197.189,91.553,5230.105,260.384,73.553,3.395]

print("splited_mod_total:", sum(splited_mod_total))

print(f"performace_boost: {100 - sum(splited_mod_total)/sum(splited_total)*100}%")