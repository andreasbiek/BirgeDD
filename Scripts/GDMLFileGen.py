import numpy as np

dest = "/Users/AndyB/Documents/School/Berkeley/Simulations/LabDose/Scripts"

coords = np.loadtxt(dest + '/' + 'Detector Coordinates.txt', skiprows=2)
name = "BirgeLab"

for i in range(0, len(coords)):
	xpos = coords[i,0]
	ypos = coords[i,1]
	zpos = coords[i,2]

	filetext = '<?xml version="1.0" encoding="UTF-8" standalone="no" ?>\n' + \
	'<gdml xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="http://service-spi.web.cern.ch/service-spi/app/releases/GDML/schema/gdml.xsd">\n' + \
	'\n' + \
	'  <define/>\n' + \
	'\n' + \
	'  <materials>\n' + \
	'    <isotope N="1" Z="1" name="H10x7ff16bf09300">\n' + \
	'      <atom unit="g/mole" value="1.00782503081372"/>\n' + \
	'    </isotope>\n' + \
	'    <isotope N="2" Z="1" name="H20x7ff16bf094f0">\n' + \
	'      <atom unit="g/mole" value="2.01410199966617"/>\n' + \
	'    </isotope>\n' + \
	'    <element name="H0x7ff16bf09530">\n' + \
	'      <fraction n="0.999885" ref="H10x7ff16bf09300"/>\n' + \
	'      <fraction n="0.000115" ref="H20x7ff16bf094f0"/>\n' + \
	'    </element>\n' + \
	'    <isotope N="12" Z="6" name="C120x7ff16bf09800">\n' + \
	'      <atom unit="g/mole" value="12"/>\n' + \
	'    </isotope>\n' + \
	'    <isotope N="13" Z="6" name="C130x7ff16bf09860">\n' + \
	'      <atom unit="g/mole" value="13.0034"/>\n' + \
	'    </isotope>\n' + \
	'    <element name="C0x7ff16bf09f80">\n' + \
	'      <fraction n="0.9893" ref="C120x7ff16bf09800"/>\n' + \
	'      <fraction n="0.0107" ref="C130x7ff16bf09860"/>\n' + \
	'    </element>\n' + \
	'    <isotope N="16" Z="8" name="O160x7ff16bf0a380">\n' + \
	'      <atom unit="g/mole" value="15.9949"/>\n' + \
	'    </isotope>\n' + \
	'    <isotope N="17" Z="8" name="O170x7ff16bf0a3c0">\n' + \
	'      <atom unit="g/mole" value="16.9991"/>\n' + \
	'    </isotope>\n' + \
	'    <isotope N="18" Z="8" name="O180x7ff16bf0a400">\n' + \
	'      <atom unit="g/mole" value="17.9992"/>\n' + \
	'    </isotope>\n' + \
	'    <element name="O0x7ff16bf0a4e0">\n' + \
	'      <fraction n="0.99757" ref="O160x7ff16bf0a380"/>\n' + \
	'      <fraction n="0.00038" ref="O170x7ff16bf0a3c0"/>\n' + \
	'      <fraction n="0.00205" ref="O180x7ff16bf0a400"/>\n' + \
	'    </element>\n' + \
	'    <isotope N="23" Z="11" name="Na230x7ff16bf0d470">\n' + \
	'      <atom unit="g/mole" value="22.9898"/>\n' + \
	'    </isotope>\n' + \
	'    <element name="Na0x7ff16bf0d8c0">\n' + \
	'      <fraction n="1" ref="Na230x7ff16bf0d470"/>\n' + \
	'    </element>\n' + \
	'    <isotope N="24" Z="12" name="Mg240x7ff16bf1c8f0">\n' + \
	'      <atom unit="g/mole" value="23.985"/>\n' + \
	'    </isotope>\n' + \
	'    <isotope N="25" Z="12" name="Mg250x7ff16bf1c2e0">\n' + \
	'      <atom unit="g/mole" value="24.9858"/>\n' + \
	'    </isotope>\n' + \
	'    <isotope N="26" Z="12" name="Mg260x7ff16bf1c320">\n' + \
	'      <atom unit="g/mole" value="25.9826"/>\n' + \
	'    </isotope>\n' + \
	'    <element name="Mg0x7ff16bf1c380">\n' + \
	'      <fraction n="0.7899" ref="Mg240x7ff16bf1c8f0"/>\n' + \
	'      <fraction n="0.1" ref="Mg250x7ff16bf1c2e0"/>\n' + \
	'      <fraction n="0.1101" ref="Mg260x7ff16bf1c320"/>\n' + \
	'    </element>\n' + \
	'    <isotope N="27" Z="13" name="Al270x7ff16bf0cbc0">\n' + \
	'      <atom unit="g/mole" value="26.9815"/>\n' + \
	'    </isotope>\n' + \
	'    <element name="Al0x7ff16bf0d0f0">\n' + \
	'      <fraction n="1" ref="Al270x7ff16bf0cbc0"/>\n' + \
	'    </element>\n' + \
	'    <isotope N="28" Z="14" name="Si280x7ff16bf0da90">\n' + \
	'      <atom unit="g/mole" value="27.9769"/>\n' + \
	'    </isotope>\n' + \
	'    <isotope N="29" Z="14" name="Si290x7ff16bf0dad0">\n' + \
	'      <atom unit="g/mole" value="28.9765"/>\n' + \
	'    </isotope>\n' + \
	'    <isotope N="30" Z="14" name="Si300x7ff16bf0db20">\n' + \
	'      <atom unit="g/mole" value="29.9738"/>\n' + \
	'    </isotope>\n' + \
	'    <element name="Si0x7ff16bf0db80">\n' + \
	'      <fraction n="0.922296077703922" ref="Si280x7ff16bf0da90"/>\n' + \
	'      <fraction n="0.0468319531680468" ref="Si290x7ff16bf0dad0"/>\n' + \
	'      <fraction n="0.0308719691280309" ref="Si300x7ff16bf0db20"/>\n' + \
	'    </element>\n' + \
	'    <isotope N="39" Z="19" name="K390x7ff16bf19510">\n' + \
	'      <atom unit="g/mole" value="38.9637"/>\n' + \
	'    </isotope>\n' + \
	'    <isotope N="40" Z="19" name="K400x7ff16bf19550">\n' + \
	'      <atom unit="g/mole" value="39.964"/>\n' + \
	'    </isotope>\n' + \
	'    <isotope N="41" Z="19" name="K410x7ff16bf19590">\n' + \
	'      <atom unit="g/mole" value="40.9618"/>\n' + \
	'    </isotope>\n' + \
	'    <element name="K0x7ff16bf195f0">\n' + \
	'      <fraction n="0.932581" ref="K390x7ff16bf19510"/>\n' + \
	'      <fraction n="0.000117" ref="K400x7ff16bf19550"/>\n' + \
	'      <fraction n="0.067302" ref="K410x7ff16bf19590"/>\n' + \
	'    </element>\n' + \
	'    <isotope N="40" Z="20" name="Ca400x7ff16bf0dd80">\n' + \
	'      <atom unit="g/mole" value="39.9626"/>\n' + \
	'    </isotope>\n' + \
	'    <isotope N="42" Z="20" name="Ca420x7ff16bf0ddc0">\n' + \
	'      <atom unit="g/mole" value="41.9586"/>\n' + \
	'    </isotope>\n' + \
	'    <isotope N="43" Z="20" name="Ca430x7ff16bf0de00">\n' + \
	'      <atom unit="g/mole" value="42.9588"/>\n' + \
	'    </isotope>\n' + \
	'    <isotope N="44" Z="20" name="Ca440x7ff16bf0de40">\n' + \
	'      <atom unit="g/mole" value="43.9555"/>\n' + \
	'    </isotope>\n' + \
	'    <isotope N="46" Z="20" name="Ca460x7ff16bf0de80">\n' + \
	'      <atom unit="g/mole" value="45.9537"/>\n' + \
	'    </isotope>\n' + \
	'    <isotope N="48" Z="20" name="Ca480x7ff16bf0bf10">\n' + \
	'      <atom unit="g/mole" value="47.9525"/>\n' + \
	'    </isotope>\n' + \
	'    <element name="Ca0x7ff16bf0e0c0">\n' + \
	'      <fraction n="0.96941" ref="Ca400x7ff16bf0dd80"/>\n' + \
	'      <fraction n="0.00647" ref="Ca420x7ff16bf0ddc0"/>\n' + \
	'      <fraction n="0.00135" ref="Ca430x7ff16bf0de00"/>\n' + \
	'      <fraction n="0.02086" ref="Ca440x7ff16bf0de40"/>\n' + \
	'      <fraction n="4e-05" ref="Ca460x7ff16bf0de80"/>\n' + \
	'      <fraction n="0.00187" ref="Ca480x7ff16bf0bf10"/>\n' + \
	'    </element>\n' + \
	'    <isotope N="54" Z="26" name="Fe540x7ff16bf12a60">\n' + \
	'      <atom unit="g/mole" value="53.9396"/>\n' + \
	'    </isotope>\n' + \
	'    <isotope N="56" Z="26" name="Fe560x7ff16bf12560">\n' + \
	'      <atom unit="g/mole" value="55.9349"/>\n' + \
	'    </isotope>\n' + \
	'    <isotope N="57" Z="26" name="Fe570x7ff16bf125a0">\n' + \
	'      <atom unit="g/mole" value="56.9354"/>\n' + \
	'    </isotope>\n' + \
	'    <isotope N="58" Z="26" name="Fe580x7ff16bf12600">\n' + \
	'      <atom unit="g/mole" value="57.9333"/>\n' + \
	'    </isotope>\n' + \
	'    <element name="Fe0x7ff16bf12640">\n' + \
	'      <fraction n="0.05845" ref="Fe540x7ff16bf12a60"/>\n' + \
	'      <fraction n="0.91754" ref="Fe560x7ff16bf12560"/>\n' + \
	'      <fraction n="0.02119" ref="Fe570x7ff16bf125a0"/>\n' + \
	'      <fraction n="0.00282" ref="Fe580x7ff16bf12600"/>\n' + \
	'    </element>\n' + \
	'    <material name="G4_CONCRETE0x7ff16bcf4980" state="solid">\n' + \
	'      <T unit="K" value="293.15"/>\n' + \
	'      <MEE unit="eV" value="135.2"/>\n' + \
	'      <D unit="g/cm3" value="2.3"/>\n' + \
	'      <fraction n="0.01" ref="H0x7ff16bf09530"/>\n' + \
	'      <fraction n="0.001" ref="C0x7ff16bf09f80"/>\n' + \
	'      <fraction n="0.529107" ref="O0x7ff16bf0a4e0"/>\n' + \
	'      <fraction n="0.016" ref="Na0x7ff16bf0d8c0"/>\n' + \
	'      <fraction n="0.002" ref="Mg0x7ff16bf1c380"/>\n' + \
	'      <fraction n="0.033872" ref="Al0x7ff16bf0d0f0"/>\n' + \
	'      <fraction n="0.337021" ref="Si0x7ff16bf0db80"/>\n' + \
	'      <fraction n="0.013" ref="K0x7ff16bf195f0"/>\n' + \
	'      <fraction n="0.044" ref="Ca0x7ff16bf0e0c0"/>\n' + \
	'      <fraction n="0.014" ref="Fe0x7ff16bf12640"/>\n' + \
	'    </material>\n' + \
	'    <material name="wood0x7ff16bf1d1e0" state="solid">\n' + \
	'      <T unit="K" value="293.15"/>\n' + \
	'      <MEE unit="eV" value="67.1996868607977"/>\n' + \
	'      <D unit="g/cm3" value="0.9"/>\n' + \
	'      <fraction n="0.0915215132472401" ref="H0x7ff16bf09530"/>\n' + \
	'      <fraction n="0.363188118343343" ref="O0x7ff16bf0a4e0"/>\n' + \
	'      <fraction n="0.545290368409417" ref="C0x7ff16bf09f80"/>\n' + \
	'    </material>\n' + \
	'    <material name="Al60610x7ff16bf1c1f0" state="solid">\n' + \
	'      <T unit="K" value="293.15"/>\n' + \
	'      <MEE unit="eV" value="166.28607227249"/>\n' + \
	'      <D unit="g/cm3" value="2.7"/>\n' + \
	'      <fraction n="0.98" ref="Al0x7ff16bf0d0f0"/>\n' + \
	'      <fraction n="0.01" ref="Mg0x7ff16bf1c380"/>\n' + \
	'      <fraction n="0.006" ref="Si0x7ff16bf0db80"/>\n' + \
	'      <fraction n="0.004" ref="Fe0x7ff16bf12640"/>\n' + \
	'    </material>\n' + \
	'    <material name="Soil0x7ff16bf1bf20" state="solid">\n' + \
	'      <T unit="K" value="293.15"/>\n' + \
	'      <MEE unit="eV" value="112.098510188939"/>\n' + \
	'      <D unit="g/cm3" value="1.5"/>\n' + \
	'      <fraction n="0.021" ref="H0x7ff16bf09530"/>\n' + \
	'      <fraction n="0.016" ref="C0x7ff16bf09f80"/>\n' + \
	'      <fraction n="0.577" ref="O0x7ff16bf0a4e0"/>\n' + \
	'      <fraction n="0.05" ref="Al0x7ff16bf0d0f0"/>\n' + \
	'      <fraction n="0.271" ref="Si0x7ff16bf0db80"/>\n' + \
	'      <fraction n="0.013" ref="K0x7ff16bf195f0"/>\n' + \
	'      <fraction n="0.041" ref="Ca0x7ff16bf0e0c0"/>\n' + \
	'      <fraction n="0.011" ref="Fe0x7ff16bf12640"/>\n' + \
	'    </material>\n' + \
	'    <material name="G4_WATER0x7ff16d8004d0" state="solid">\n' + \
	'      <T unit="K" value="293.15"/>\n' + \
	'      <MEE unit="eV" value="78"/>\n' + \
	'      <D unit="g/cm3" value="1"/>\n' + \
	'      <fraction n="0.111898477841067" ref="H0x7ff16bf09530"/>\n' + \
	'      <fraction n="0.888101522158933" ref="O0x7ff16bf0a4e0"/>\n' + \
	'    </material>\n' + \
	'    <isotope N="14" Z="7" name="N140x7ff16bf0a130">\n' + \
	'      <atom unit="g/mole" value="14.0031"/>\n' + \
	'    </isotope>\n' + \
	'    <isotope N="15" Z="7" name="N150x7ff16bf0a1b0">\n' + \
	'      <atom unit="g/mole" value="15.0001"/>\n' + \
	'    </isotope>\n' + \
	'    <element name="N0x7ff16bf0a1f0">\n' + \
	'      <fraction n="0.99632" ref="N140x7ff16bf0a130"/>\n' + \
	'      <fraction n="0.00368" ref="N150x7ff16bf0a1b0"/>\n' + \
	'    </element>\n' + \
	'    <isotope N="36" Z="18" name="Ar360x7ff16bf0a670">\n' + \
	'      <atom unit="g/mole" value="35.9675"/>\n' + \
	'    </isotope>\n' + \
	'    <isotope N="38" Z="18" name="Ar380x7ff16bf0a6b0">\n' + \
	'      <atom unit="g/mole" value="37.9627"/>\n' + \
	'    </isotope>\n' + \
	'    <isotope N="40" Z="18" name="Ar400x7ff16bf0a6f0">\n' + \
	'      <atom unit="g/mole" value="39.9624"/>\n' + \
	'    </isotope>\n' + \
	'    <element name="Ar0x7ff16bf0a730">\n' + \
	'      <fraction n="0.003365" ref="Ar360x7ff16bf0a670"/>\n' + \
	'      <fraction n="0.000632" ref="Ar380x7ff16bf0a6b0"/>\n' + \
	'      <fraction n="0.996003" ref="Ar400x7ff16bf0a6f0"/>\n' + \
	'    </element>\n' + \
	'    <material name="Air0x7ff16bf09e90" state="gas">\n' + \
	'      <T unit="K" value="293.15"/>\n' + \
	'      <MEE unit="eV" value="85.7"/>\n' + \
	'      <D unit="g/cm3" value="0.00120479"/>\n' + \
	'      <fraction n="0.000124000124000124" ref="C0x7ff16bf09f80"/>\n' + \
	'      <fraction n="0.755267755267755" ref="N0x7ff16bf0a1f0"/>\n' + \
	'      <fraction n="0.231781231781232" ref="O0x7ff16bf0a4e0"/>\n' + \
	'      <fraction n="0.0128270128270128" ref="Ar0x7ff16bf0a730"/>\n' + \
	'    </material>\n' + \
	'  </materials>\n' + \
	'\n' + \
	'  <solids>\n' + \
	'    <box lunit="mm" name="z_wall0x7ff16bcf5490" x="8648.7" y="8039.1" z="266.7"/>\n' + \
	'    <box lunit="mm" name="x_wall_short0x7ff16bcf4ef0" x="6261.1" y="266.7" z="3492.5"/>\n' + \
	'    <box lunit="mm" name="x_wall_long0x7ff16bcf50b0" x="7632.7" y="127" z="3492.5"/>\n' + \
	'    <box lunit="mm" name="y_wall_left0x7ff16bcf5ff0" x="266.7" y="6629.4" z="3492.5"/>\n' + \
	'    <box lunit="mm" name="y_wall_right0x7ff16bcf61b0" x="152.4" y="4800.6" z="3492.5"/>\n' + \
	'    <box lunit="mm" name="x_wall_adj_door0x7ff16bcf6330" x="1219.2" y="152.4" z="3492.5"/>\n' + \
	'    <box lunit="mm" name="cupboard_OV0x7ff16bcf64d0" x="685.8" y="1511.3" z="914.4"/>\n' + \
	'    <box lunit="mm" name="cupboard_IV0x7ff16bcf6540" x="635" y="1460.5" z="863.6"/>\n' + \
	'    <subtraction name="cupboard0x7ff16bcf65b0">\n' + \
	'      <first ref="cupboard_OV0x7ff16bcf64d0"/>\n' + \
	'      <second ref="cupboard_IV0x7ff16bcf6540"/>\n' + \
	'    </subtraction>\n' + \
	'    <box lunit="mm" name="pump_room_OV0x7ff16d800040" x="1308.1" y="2590.8" z="3492.5"/>\n' + \
	'    <box lunit="mm" name="pump_room_IV0x7ff16d8000b0" x="1206.5" y="2489.2" z="3492.5"/>\n' + \
	'    <subtraction name="pump_room0x7ff16d800120">\n' + \
	'      <first ref="pump_room_OV0x7ff16d800040"/>\n' + \
	'      <second ref="pump_room_IV0x7ff16d8000b0"/>\n' + \
	'    </subtraction>\n' + \
	'    <tube aunit="deg" deltaphi="360" lunit="mm" name="platform_pillar0x7ff16bdd5020" rmax="127" rmin="0" startphi="0" z="2057.4"/>\n' + \
	'    <xtru lunit="mm" name="platform_tri_pri0x7ff16c82ae00">\n' + \
	'      <twoDimVertex x="-2057.4" y="-1257.3"/>\n' + \
	'      <twoDimVertex x="-2057.4" y="1257.3"/>\n' + \
	'      <twoDimVertex x="0" y="0"/>\n' + \
	'      <section scalingFactor="1" xOffset="0" yOffset="0" zOrder="0" zPosition="-177.8"/>\n' + \
	'      <section scalingFactor="1" xOffset="0" yOffset="0" zOrder="1" zPosition="177.8"/>\n' + \
	'    </xtru>\n' + \
	'    <tube aunit="deg" deltaphi="360" lunit="mm" name="platform_hole0x7ff16bdd59d0" rmax="317.5" rmin="0" startphi="0" z="177.8"/>\n' + \
	'    <subtraction name="platform0x7ff16bdd5740">\n' + \
	'      <first ref="platform_tri_pri0x7ff16c82ae00"/>\n' + \
	'      <second ref="platform_hole0x7ff16bdd59d0"/>\n' + \
	'      <position name="platform0x7ff16bdd5740_pos" unit="mm" x="-1346.2" y="0" z="0"/>\n' + \
	'    </subtraction>\n' + \
	'    <box lunit="mm" name="world_box0x7ff16bcf3e70" x="9664.7" y="9055.1" z="6324.6"/>\n' + \
	'    <box lunit="mm" name="building_space0x7ff16bf205c0" x="8648.7" y="8039.1" z="5308.6"/>\n' + \
	'    <subtraction name="soil_space0x7ff16bf1f960">\n' + \
	'      <first ref="world_box0x7ff16bcf3e70"/>\n' + \
	'      <second ref="building_space0x7ff16bf205c0"/>\n' + \
	'      <position name="soil_space0x7ff16bf1f960_pos" unit="mm" x="508" y="-508" z="508"/>\n' + \
	'    </subtraction>\n' + \
	'    <box lunit="mm" name="dose_box0x7ff16d800460" x="250" y="250" z="250"/>\n' + \
	'  </solids>\n' + \
	'\n' + \
	'  <structure>\n' + \
	'    <volume name="z_wall_LV0x7ff16bcf4d40">\n' + \
	'      <materialref ref="G4_CONCRETE0x7ff16bcf4980"/>\n' + \
	'      <solidref ref="z_wall0x7ff16bcf5490"/>\n' + \
	'    </volume>\n' + \
	'    <volume name="x_wall_short_LV0x7ff16bcf4f60">\n' + \
	'      <materialref ref="G4_CONCRETE0x7ff16bcf4980"/>\n' + \
	'      <solidref ref="x_wall_short0x7ff16bcf4ef0"/>\n' + \
	'    </volume>\n' + \
	'    <volume name="x_wall_long_LV0x7ff16bcf5120">\n' + \
	'      <materialref ref="G4_CONCRETE0x7ff16bcf4980"/>\n' + \
	'      <solidref ref="x_wall_long0x7ff16bcf50b0"/>\n' + \
	'    </volume>\n' + \
	'    <volume name="y_wall_left_LV0x7ff16bcf6060">\n' + \
	'      <materialref ref="G4_CONCRETE0x7ff16bcf4980"/>\n' + \
	'      <solidref ref="y_wall_left0x7ff16bcf5ff0"/>\n' + \
	'    </volume>\n' + \
	'    <volume name="y_wall_right_LV0x7ff16bcf6220">\n' + \
	'      <materialref ref="G4_CONCRETE0x7ff16bcf4980"/>\n' + \
	'      <solidref ref="y_wall_right0x7ff16bcf61b0"/>\n' + \
	'    </volume>\n' + \
	'    <volume name="x_wall_adj_door_LV0x7ff16bcf63a0">\n' + \
	'      <materialref ref="G4_CONCRETE0x7ff16bcf4980"/>\n' + \
	'      <solidref ref="x_wall_adj_door0x7ff16bcf6330"/>\n' + \
	'    </volume>\n' + \
	'    <volume name="cupboard_LV0x7ff16bcf6740">\n' + \
	'      <materialref ref="wood0x7ff16bf1d1e0"/>\n' + \
	'      <solidref ref="cupboard0x7ff16bcf65b0"/>\n' + \
	'    </volume>\n' + \
	'    <volume name="pump_room_LV0x7ff16d8002b0">\n' + \
	'      <materialref ref="wood0x7ff16bf1d1e0"/>\n' + \
	'      <solidref ref="pump_room0x7ff16d800120"/>\n' + \
	'    </volume>\n' + \
	'    <volume name="platform_pillar_LV0x7ff16bdd5100">\n' + \
	'      <materialref ref="Al60610x7ff16bf1c1f0"/>\n' + \
	'      <solidref ref="platform_pillar0x7ff16bdd5020"/>\n' + \
	'    </volume>\n' + \
	'    <volume name="platform_LV0x7ff16bdd63e0">\n' + \
	'      <materialref ref="Al60610x7ff16bf1c1f0"/>\n' + \
	'      <solidref ref="platform0x7ff16bdd5740"/>\n' + \
	'    </volume>\n' + \
	'    <volume name="soil_space_LV0x7ff16bf1fd40">\n' + \
	'      <materialref ref="Soil0x7ff16bf1bf20"/>\n' + \
	'      <solidref ref="soil_space0x7ff16bf1f960"/>\n' + \
	'    </volume>\n' + \
	'    <volume name="dose_box_LV0x7ff16d800840">\n' + \
	'      <materialref ref="G4_WATER0x7ff16d8004d0"/>\n' + \
	'      <solidref ref="dose_box0x7ff16d800460"/>\n' + \
	'    </volume>\n' + \
	'    <volume name="WorldLV0x7ff16bcf4880">\n' + \
	'      <materialref ref="Air0x7ff16bf09e90"/>\n' + \
	'      <solidref ref="world_box0x7ff16bcf3e70"/>\n' + \
	'      <physvol name="z_wall_PV_10x7ff16bcf4dd0">\n' + \
	'        <volumeref ref="z_wall_LV0x7ff16bcf4d40"/>\n' + \
	'        <position name="z_wall_PV_10x7ff16bcf4dd0_pos" unit="mm" x="508" y="-508" z="1879.6"/>\n' + \
	'      </physvol>\n' + \
	'      <physvol copynumber="1" name="z_wall_PV_20x7ff16bcf4e80">\n' + \
	'        <volumeref ref="z_wall_LV0x7ff16bcf4d40"/>\n' + \
	'        <position name="z_wall_PV_20x7ff16bcf4e80_pos" unit="mm" x="508" y="-508" z="-1879.6"/>\n' + \
	'      </physvol>\n' + \
	'      <physvol name="x_wall_short_PV0x7ff16bcf5020">\n' + \
	'        <volumeref ref="x_wall_short_LV0x7ff16bcf4f60"/>\n' + \
	'        <position name="x_wall_short_PV0x7ff16bcf5020_pos" unit="mm" x="-685.8" y="3378.2" z="0"/>\n' + \
	'      </physvol>\n' + \
	'      <physvol name="x_wall_long_PV0x7ff16bcf5fa0">\n' + \
	'        <volumeref ref="x_wall_long_LV0x7ff16bcf5120"/>\n' + \
	'        <position name="x_wall_long_PV0x7ff16bcf5fa0_pos" unit="mm" x="0" y="-3448.05" z="0"/>\n' + \
	'      </physvol>\n' + \
	'      <physvol name="y_wall_left_PV0x7ff16bcf6120">\n' + \
	'        <volumeref ref="y_wall_left_LV0x7ff16bcf6060"/>\n' + \
	'        <position name="y_wall_left_PV0x7ff16bcf6120_pos" unit="mm" x="-3683" y="-69.85" z="0"/>\n' + \
	'      </physvol>\n' + \
	'      <physvol name="y_wall_right_PV0x7ff16bcf62e0">\n' + \
	'        <volumeref ref="y_wall_right_LV0x7ff16bcf6220"/>\n' + \
	'        <position name="y_wall_right_PV0x7ff16bcf62e0_pos" unit="mm" x="2368.55" y="844.55" z="0"/>\n' + \
	'      </physvol>\n' + \
	'      <physvol name="x_wall_adj_door_PV0x7ff16bcf6460">\n' + \
	'        <volumeref ref="x_wall_adj_door_LV0x7ff16bcf63a0"/>\n' + \
	'        <position name="x_wall_adj_door_PV0x7ff16bcf6460_pos" unit="mm" x="3054.35" y="-1479.55" z="0"/>\n' + \
	'      </physvol>\n' + \
	'      <physvol name="cupboard_PV0x7ff16bcf6800">\n' + \
	'        <volumeref ref="cupboard_LV0x7ff16bcf6740"/>\n' + \
	'        <position name="cupboard_PV0x7ff16bcf6800_pos" unit="mm" x="1949.45" y="2489.2" z="-1289.05"/>\n' + \
	'      </physvol>\n' + \
	'      <physvol name="pump_room_PV0x7ff16d800370">\n' + \
	'        <volumeref ref="pump_room_LV0x7ff16d8002b0"/>\n' + \
	'        <position name="pump_room_PV0x7ff16d800370_pos" unit="mm" x="-2895.6" y="-2089.15" z="0"/>\n' + \
	'      </physvol>\n' + \
	'      <physvol name="platform_pillar_PV0x7ff16bdd51c0">\n' + \
	'        <volumeref ref="platform_pillar_LV0x7ff16bdd5100"/>\n' + \
	'        <position name="platform_pillar_PV0x7ff16bdd51c0_pos" unit="mm" x="-1492.25" y="1758.95" z="-717.55"/>\n' + \
	'      </physvol>\n' + \
	'      <physvol name="platform_PV0x7ff16bdd60e0">\n' + \
	'        <volumeref ref="platform_LV0x7ff16bdd63e0"/>\n' + \
	'        <position name="platform_PV0x7ff16bdd60e0_pos" unit="mm" x="-1492.25" y="1758.95" z="488.95"/>\n' + \
	'      </physvol>\n' + \
	'      <physvol name="soil_space_PV0x7ff16bf1fa90">\n' + \
	'        <volumeref ref="soil_space_LV0x7ff16bf1fd40"/>\n' + \
	'      </physvol>\n' + \
	'      <physvol name="dose_box_PV0x7ff16d8007a0">\n' + \
	'        <volumeref ref="dose_box_LV0x7ff16d800840"/>\n' + \
	'        <position name="dose_box_PV0x7ff16d8007a0_pos" unit="mm" x="' + str(xpos) + '" y="' + str(ypos) + '" z="' + str(zpos) + '"/>\n' + \
	'      </physvol>\n' + \
	'    </volume>\n' + \
	'  </structure>\n' + \
	'\n' + \
	'  <setup name="Default" version="1.0">\n' + \
	'    <world ref="WorldLV0x7ff16bcf4880"/>\n' + \
	'  </setup>\n' + \
	'\n' + \
	'</gdml>\n'
	f = open(dest + '/GDML Files/' + name + str(i) + ".gdml", "w")
	f.write(filetext)
	f.close()