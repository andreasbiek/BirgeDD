import numpy as np

dest = "/Users/AndyB/Documents/School/Berkeley/Simulations/LabDose/Scripts"

coords = np.loadtxt(dest + '/' + 'Detector Coordinates.txt', skiprows=2)
name = "BirgeLab"

for i in range(0, len(coords)):

	filetext = "/run/initialize\n" + \
            "/tracking/verbose 0\n" + \
            "/random/setSeeds " + str(i + 1000) + " " + str(13*i + 1000) +"\n" + \
            "\n" + \
            "# list the existing physics processes\n" + \
            "/process/list\n" + \
            "\n" + \
            "/gps/particle neutron\n" + \
            "/gps/pos/centre 31.75 1720.8 -745.0 mm\n" + \
            "/gps/pos/type Point\n" + \
            "/gps/ang/type iso\n" + \
            "\n" + \
            "/gps/ene/type Mono\n" + \
            "/gps/ene/mono 2.8 MeV\n" + \
            "\n" + \
            "/run/printProgress 10000\n" + \
            "/analysis/setFileName BirgeLab" + str(i) + "\n" \
            "\n" + \
            "/run/beamOn 100000"
	f = open(dest + '/Macro Files/' + name + str(i) + ".mac", "w")
	f.write(filetext)
	f.close()