import subprocess
import os

for folder in ["branch1", "branch2", "branch3"]:
    path = os.path.join("../InputPictures/", folder)
    for file in os.listdir(path):
        filepath = os.path.join(path, file)
        if not file.endswith(".png"):
            continue

        # if file.endswith(".csv"):
        #     os.remove(filepath)
        #     continue 

        # print(f"./centreLineOut {filepath}")
        subprocess.run(f"./centreLineOut {filepath}", shell=True)

# subprocess.run("./centreLineOut ", shell=True)