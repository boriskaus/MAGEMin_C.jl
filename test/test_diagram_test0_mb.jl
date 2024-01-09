# This checks the diagram produced by test4  (=Gt-migmatite)
#

list  = [outP{Float64}(0.01, 600.0, 0, -833.0108853505229, ["fsp", "sp", "aug", "opx", "ilm", "fsp", "ilm", "q", "H2O"], [0.01797537374122556, 0.013211075597411387, 0.18723591009191284, 0.14728916291566707, 0.014242242289883647, 0.42569540748340984, 0.010265595904406927, 0.008744047253957547, 0.17534118472193816]),
outP{Float64}(0.01, 700.0, 0, -846.0300815738545, ["fsp", "fsp", "opx", "sp", "ilm", "aug", "q", "H2O"], [0.01698154415562998, 0.4242169702433358, 0.1500780896985816, 0.0058061049858312425, 0.029119280202569365, 0.19231581446037843, 0.006141011532945731, 0.17534118472193816]),
outP{Float64}(0.01, 800.0, 0, -859.744363741313, ["opx", "fsp", "sp", "fsp", "ilm", "aug", "q", "H2O"], [0.14586629983544605, 0.014924104027832326, 0.0067051010381108354, 0.4230197069946455, 0.027703697790266966, 0.19916252476831237, 0.007277380949125813, 0.17534118472193813]),
outP{Float64}(0.01, 900.0, 0, -874.1055430801866, ["opx", "fsp", "ilm", "sp", "liq", "aug", "H2O"], [0.13856959907127642, 0.4177903554405236, 0.025144338942200087, 0.00910124926574977, 0.026941089575495524, 0.20727302908653764, 0.17518046671593798]),
outP{Float64}(0.01, 1000.0, 0, -889.0820365815389, ["fsp", "opx", "liq", "sp", "ilm", "aug", "H2O"], [0.3841432281761848, 0.12038722428481274, 0.07003729403364362, 0.010560026968043461, 0.02326027739050085, 0.2167252134040766, 0.1748868629969604]),
outP{Float64}(0.01, 1100.0, 0, -904.7443024789643, ["ilm", "opx", "liq", "fsp", "aug", "H2O"], [0.02812250202950872, 0.058746414085355685, 0.2625238218366626, 0.25974762027235637, 0.21712802918958365, 0.1737324976446339]),
outP{Float64}(0.01, 1200.0, 0, -921.1825225101582, ["ilm", "aug", "liq", "fsp", "ru", "H2O"], [0.022982383561049115, 0.20481566328423992, 0.4682498764487576, 0.12965155291509914, 0.0017501358167637715, 0.17255162147943046]),
outP{Float64}(4.01, 600.0, 0, -820.2199891066532, ["fsp", "hb", "bi", "q", "sph", "H2O"], [0.2332658138303998, 0.5377936761788078, 0.014372080550404634, 0.059391423177534805, 0.019790017632123715, 0.1353869886345003]),
outP{Float64}(4.01, 700.0, 0, -831.9231109485354, ["hb", "fsp", "liq", "aug", "q", "sph", "H2O"], [0.5413803585534064, 0.22354912758555656, 0.03352490777403511, 0.005874670628902849, 0.0494884071364235, 0.01620390694733722, 0.12997862137820937]),
outP{Float64}(4.01, 800.0, 0, -844.4825513335911, ["hb", "fsp", "aug", "ilm", "liq", "H2O"], [0.4509365646628561, 0.1555072729673364, 0.07101791703065503, 0.010741377365478564, 0.21907662659239405, 0.09271970120317984]),
outP{Float64}(4.01, 900.0, 0, -857.8815751481777, ["fsp", "liq", "ilm", "hb", "aug", "H2O"], [0.09124601802561422, 0.3309575507301219, 0.010455759576065711, 0.3680474650613859, 0.12555504826560546, 0.07374105889138093]),
outP{Float64}(4.01, 1000.0, 0, -872.1437662282287, ["liq", "aug", "fsp", "hb", "ilm", "H2O"], [0.5494934876350699, 0.19420070552021035, 0.00917964169853423, 0.19246686840432814, 0.014769447334191284, 0.039892889822879966]),
outP{Float64}(4.01, 1100.0, 0, -887.3798023815874, ["ilm", "liq", "aug", "H2O"], [0.026732367878569734, 0.7538438266652928, 0.21163158895979134, 0.0077918390344715585]),
outP{Float64}(4.01, 1200.0, 0, -903.4213318004882, ["liq", "aug", "ilm", "ru"], [0.8470180389668374, 0.12338977667186907, 0.028828790744651472, 0.0007661566742633475]),
outP{Float64}(8.01, 600.0, 0, -812.2017264860988, ["fsp", "aug", "bi", "ep", "hb", "q", "sph", "H2O"], [0.10409834521927122, 0.01675656533796699, 0.013680871166581655, 0.058797649802954766, 0.560642066565606, 0.09657814372527099, 0.01945545349689264, 0.1299909046853238]),
outP{Float64}(8.01, 700.0, 0, -823.771396367982, ["hb", "liq", "aug", "fsp", "q", "sph", "H2O"], [0.5498111449704954, 0.09991183215021239, 0.04612013712778769, 0.11328599478171479, 0.07078027181081865, 0.01605809892892795, 0.10403252022733947]),
outP{Float64}(8.01, 800.0, 0, -836.2695760829575, ["hb", "fsp", "aug", "liq", "sph", "H2O"], [0.5062905394116495, 0.01548830460988284, 0.08092140728844732, 0.36047259684876914, 0.011145686308854319, 0.025684496413227075]),
outP{Float64}(8.01, 900.0, 0, -849.6221163238408, ["liq", "aug", "hb", "ilm", "H2O"], [0.46067726673868997, 0.14363041877813593, 0.38454080132449064, 0.009116513227286531, 0.0020394423831072025]),
outP{Float64}(8.01, 1000.0, 0, -863.8192021410279, ["hb", "liq", "aug", "ilm"], [0.21186339468892182, 0.5744722104408677, 0.19887493198430872, 0.014803966984259963]),
outP{Float64}(8.01, 1100.0, 0, -878.8922861444905, ["liq", "aug", "opx", "ilm", "ru"], [0.72153491622804, 0.24363917541994615, 0.010784736186030715, 0.0227790851417032, 0.0012733336731680575]),
outP{Float64}(8.01, 1200.0, 0, -894.7552181668892, ["liq", "aug", "ilm", "ru"], [0.7959576901552338, 0.17856421119511423, 0.023141217837643054, 0.002341053920205842]),
outP{Float64}(12.01, 600.0, 0, -804.5540944919305, ["aug", "mu", "bi", "ep", "hb", "q", "sph", "H2O"], [0.02652468532510799, 0.012464615241333174, 0.007536562322464607, 0.12006435692956074, 0.5815326863062182, 0.1092233378125856, 0.019300623966089153, 0.12335313209608262]),
outP{Float64}(12.01, 700.0, 0, -815.9711812532756, ["hb", "ep", "liq", "aug", "q", "sph", "H2O"], [0.567927241689723, 0.06905660926425261, 0.15869667376097768, 0.038717553239319066, 0.08187547757248509, 0.016047942998689124, 0.0676780872553437]),
outP{Float64}(12.01, 800.0, 0, -828.3529904704692, ["hb", "g", "liq", "aug", "ru", "sph"], [0.45424333327146715, 0.035130638100798244, 0.396183553628864, 0.10849458106657818, 0.004735994803468599, 0.0012288621791786086]),
outP{Float64}(12.01, 900.0, 0, -841.6161359356496, ["aug", "g", "liq", "hb", "ilm", "ru"], [0.15427297327484393, 0.0336500597996629, 0.44546479257380556, 0.360196331679044, 0.0029593959286942596, 0.003469165851715572]),
outP{Float64}(12.01, 1000.0, 0, -855.6903400723498, ["liq", "hb", "ilm", "aug"], [0.5421740890380791, 0.23518427977281461, 0.013782669533655537, 0.20887398367872667]),
outP{Float64}(12.01, 1100.0, 0, -870.6002345373568, ["liq", "aug", "opx", "ilm", "hb", "ru"], [0.674490636428777, 0.26136616441090843, 0.013314662279170301, 0.017917979427202867, 0.0306521487348862, 0.0022760523245605887]),
outP{Float64}(12.01, 1200.0, 0, -886.3021604940946, ["ilm", "aug", "liq", "ru"], [0.01825203519264284, 0.22252418035367677, 0.7554419431350061, 0.003787915790293091]),
outP{Float64}(16.01, 600.0, 0, -797.1277672939711, ["mu", "hb", "ep", "aug", "q", "ru", "H2O"], [0.02303284434443357, 0.5688441613772255, 0.19642705875860667, 0.014286714734760548, 0.0715838562876135, 0.0076923639832754305, 0.11813450331557408]),
outP{Float64}(16.01, 700.0, 0, -808.389863189471, ["hb", "g", "ep", "liq", "aug", "q", "ru", "H2O"], [0.5062626039501584, 0.03756388718613553, 0.10459075372326238, 0.08828331919235903, 0.0717011261558881, 0.09173792063842436, 0.006607922215135108, 0.09325900656623011]),
outP{Float64}(16.01, 800.0, 0, -820.6592206829049, ["liq", "g", "hb", "aug", "ru"], [0.3971239874722414, 0.21810485112590403, 0.2778254392607096, 0.09969346157865289, 0.0072522605603508915]),
outP{Float64}(16.01, 900.0, 0, -833.8343759319939, ["liq", "g", "hb", "aug", "ru"], [0.4439549081373423, 0.2470700402348331, 0.15119195832034793, 0.15018398510447195, 0.007612787001144082]),
outP{Float64}(16.01, 1000.0, 0, -847.7800589878234, ["aug", "g", "hb", "liq", "ru"], [0.207176532131942, 0.2364998508862055, 0.038146746967805976, 0.509562529422464, 0.008629418392483473]),
outP{Float64}(16.01, 1100.0, 0, -862.5039592180531, ["ilm", "liq", "aug", "g", "ru"], [0.0027169688327039095, 0.6098121913805938, 0.24437782286770185, 0.1348266744119364, 0.008279876615019997]),
outP{Float64}(16.01, 1200.0, 0, -878.0214094736839, ["ilm", "liq", "aug", "ru"], [0.013954659828412786, 0.7214959723096448, 0.25945796784845315, 0.0051008552638672966]),
outP{Float64}(20.01, 600.0, 0, -789.9128506748232, ["g", "hb", "aug", "mu", "hb", "ep", "q", "ru", "H2O"], [0.11943848231931042, 0.3670332378212121, 0.0017299882179357129, 0.02800544068385789, 0.07756752780002069, 0.2370802103872481, 0.037527377051971955, 0.008607488060966796, 0.12301024765779237]),
outP{Float64}(20.01, 700.0, 0, -801.0558460543853, ["g", "hb", "mu", "ep", "aug", "q", "ru", "H2O"], [0.15161797987695372, 0.33862289238697124, 0.025954652294952158, 0.11120436730143267, 0.13309365036994905, 0.09141512415990519, 0.007868338854128009, 0.14022309241120898]),
outP{Float64}(20.01, 800.0, 0, -813.1903793325666, ["g", "liq", "aug", "ep", "hb", "q", "ru"], [0.3386678499118716, 0.393159978066592, 0.1683037317563958, 0.007464819834556657, 0.08255459271610882, 0.0011432272139595273, 0.008705800500029802]),
outP{Float64}(20.01, 900.0, 0, -826.2901698729811, ["g", "liq", "aug", "ru"], [0.3720264547929807, 0.4376098341922211, 0.1811733894719787, 0.009205412197901752]),
outP{Float64}(20.01, 1000.0, 0, -840.1023635605543, ["g", "liq", "aug", "ru"], [0.3326183705981954, 0.47715424441052273, 0.18103522106101164, 0.009205412197901752]),
outP{Float64}(20.01, 1100.0, 0, -854.6306149447886, ["g", "liq", "aug", "ru"], [0.2394349046800889, 0.5510188280638502, 0.20035559397339878, 0.009205412197901752]),
outP{Float64}(20.01, 1200.0, 0, -869.9168035049586, ["aug", "liq", "g", "ru"], [0.2215794585470618, 0.652883516185617, 0.11634397658953692, 0.009205412197901752]),
outP{Float64}(24.01, 600.0, 0, -782.8474362819605, ["hb", "g", "ep", "mu", "aug", "q", "ru", "H2O"], [0.3547419192372746, 0.18317211002169378, 0.19612711627141594, 0.028111608387902116, 0.051041310119618565, 0.04577540930052668, 0.008783221349128617, 0.13224734010421133]),
outP{Float64}(24.01, 700.0, 0, -793.9431960357779, ["aug", "mu", "g", "ep", "q", "ky", "ru", "H2O"], [0.3813459599092918, 0.029991211049520235, 0.27121307197728833, 0.0110235828346255, 0.06861003098871708, 0.05830561296306511, 0.009205412197901752, 0.17030511808003546]),
outP{Float64}(24.01, 800.0, 0, -805.934109877481, ["aug", "g", "liq", "q", "ky", "ru", "H2O"], [0.28904580019563275, 0.343219848600512, 0.23340497370505114, 0.030314314706389393, 0.03024399803438021, 0.009205412197901752, 0.06456565255991922]),
outP{Float64}(24.01, 900.0, 0, -818.8929677182163, ["g", "liq", "aug", "ru"], [0.3814091098440194, 0.41236567423922976, 0.1970345406291142, 0.009205412197901752]),
outP{Float64}(24.01, 1000.0, 0, -832.5705126823142, ["aug", "liq", "g", "ru"], [0.18266893663485215, 0.44872835799197025, 0.3594121010134999, 0.009205412197901752]),
outP{Float64}(24.01, 1100.0, 0, -846.9302236340106, ["g", "liq", "aug", "ru"], [0.31118667911092135, 0.504949879182244, 0.17467246444891674, 0.009205412197901752]),
outP{Float64}(24.01, 1200.0, 0, -862.007802292437, ["liq", "g", "aug", "ru"], [0.5986555700860205, 0.20715679439453435, 0.18499621964243726, 0.009205412197901752])
]
            

