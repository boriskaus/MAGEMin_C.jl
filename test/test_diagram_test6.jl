# This checks the diagram produced by test6
#

list = [outP{Float64}(0.01, 800.0, 6, -922.1346791265483, ["fsp", "cpx", "ol", "spn", "fl", "ilm", "opx"], [0.4852711561375254, 0.24352478953322615, 0.02177720545988645, 0.004910473018183622, 0.06325527544910077, 0.01607971791817678, 0.16517897513835114]),
outP{Float64}(0.01, 900.0, 6, -935.605337911674, ["fsp", "fl", "ol", "ilm", "spn", "cpx", "opx"], [0.4768597619105533, 0.06723211976649036, 0.018260144936547314, 0.015325070781949375, 0.004525388355880118, 0.25921025870207026, 0.15858656052545364]),
outP{Float64}(0.01, 1000.0, 6, -949.7133368972953, ["fsp", "spn", "ol", "ilm", "fl", "cpx", "opx"], [0.46364859695892946, 0.0046355185595689935, 0.012162698845763657, 0.013775368778033344, 0.07391364227341483, 0.28930991755809715, 0.1425428945452708]),
outP{Float64}(0.01, 1100.0, 6, -964.6891504245604, ["ol", "liq", "fl", "fsp", "cpx"], [0.08251065638152193, 0.4555089300511277, 0.07239203926726216, 0.2583016842013311, 0.1312992983974944]),
outP{Float64}(0.01, 1200.0, 6, -981.1915769939299, ["fl", "liq"], [0.06917679176715243, 0.9308328530967451]),
outP{Float64}(0.01, 1300.0, 6, -998.6059095272891, ["liq", "fl"], [0.9273700842881093, 0.07263087157067764]),
outP{Float64}(0.01, 1400.0, 6, -1016.6129827660201, ["liq", "fl"], [0.9237103369669901, 0.07629106315519345]),
outP{Float64}(5.01, 800.0, 6, -909.6069816324189, ["fsp", "hb", "liq", "cpx", "opx", "ilm"], [0.26287521845803025, 0.4316677975221895, 0.1374315982333979, 0.140160494160625, 0.01907326059035448, 0.008811195518225014]),
outP{Float64}(5.01, 900.0, 6, -922.760379476909, ["hb", "fsp", "liq", "ilm", "cpx", "opx"], [0.21031339916906178, 0.25417423314084253, 0.21449356320601926, 0.007413944842114159, 0.22508648447210672, 0.08847411571358234]),
outP{Float64}(5.01, 1000.0, 6, -936.7936662227761, ["hb", "cpx", "liq", "fsp", "opx"], [0.02474760003064984, 0.263331575346195, 0.4020108048767874, 0.2093872607621445, 0.10054203906279313]),
outP{Float64}(5.01, 1100.0, 6, -951.9866486741887, ["liq", "cpx", "fsp", "opx"], [0.7894738102166743, 0.15265970545516866, 0.05760595848446383, 0.000300906105422783]),
outP{Float64}(5.01, 1200.0, 6, -968.4620279399197, ["liq"], [1.0000020884619987]),
outP{Float64}(5.01, 1300.0, 6, -985.6826807813104, ["liq"], [0.9999971376346095]),
outP{Float64}(5.01, 1400.0, 6, -1003.4974878473731, ["liq"], [0.999996577652062]),
outP{Float64}(10.01, 800.0, 6, -899.5002905310917, ["fsp", "hb", "liq", "cpx", "q", "ru"], [0.15007650172096698, 0.5268545909068587, 0.09324000572403297, 0.166455883909042, 0.0602133573817681, 0.0030906150251100253]),
outP{Float64}(10.01, 900.0, 6, -912.5469218667026, ["liq", "hb", "fsp", "cpx", "ilm", "opx"], [0.20955302089571134, 0.2905294098371687, 0.20648116510302783, 0.25301425858709703, 0.0027057143732283364, 0.03761851257763311]),
outP{Float64}(10.01, 1000.0, 6, -926.4627239659222, ["cpx", "fsp", "hb", "liq", "opx"], [0.3124628339235903, 0.18683838503220127, 0.10445895081541344, 0.3328199176909555, 0.06341237210039624]),
outP{Float64}(10.01, 1100.0, 6, -941.3979565747819, ["cpx", "liq", "fsp", "opx"], [0.274954089407908, 0.6312591947865537, 0.08051677062346706, 0.013300629180602572]),
outP{Float64}(10.01, 1200.0, 6, -957.5475916498243, ["cpx", "liq"], [0.04036048068895971, 0.9596522878517675]),
outP{Float64}(10.01, 1300.0, 6, -974.668752412599, ["liq"], [0.9999991489972978]),
outP{Float64}(10.01, 1400.0, 6, -992.3867024078611, ["liq"], [0.9999995310925879]),
outP{Float64}(15.01, 800.0, 6, -889.7692645695112, ["g", "liq", "fsp", "cpx", "hb", "q", "ru"], [0.20383522834195178, 0.12314347512301886, 0.025814794657865122, 0.23061397715571763, 0.32445991298669086, 0.0864971989143579, 0.0055475891326267155]),
outP{Float64}(15.01, 900.0, 6, -902.7386648259329, ["g", "liq", "cpx", "fsp", "ru"], [0.3260018004627214, 0.2627170744927335, 0.32019960370387734, 0.08499412388642107, 0.006014239595623453]),
outP{Float64}(15.01, 1000.0, 6, -916.5549024979161, ["liq", "g", "fsp", "cpx"], [0.35965964469865425, 0.28195338177239915, 0.042496408703693055, 0.3158425191909107]),
outP{Float64}(15.01, 1100.0, 6, -931.2228034259826, ["liq", "g", "cpx"], [0.5185625107291804, 0.19097480681714363, 0.2904279867372037]),
outP{Float64}(15.01, 1200.0, 6, -946.9663978566487, ["liq", "cpx"], [0.8143388846726504, 0.18567882482889328]),
outP{Float64}(15.01, 1300.0, 6, -963.8806587427188, ["liq"], [0.9999991970087679]),
outP{Float64}(15.01, 1400.0, 6, -981.5083061279147, ["liq"], [0.999999724431445]),
outP{Float64}(20.01, 800.0, 6, -880.5305721596446, ["liq", "g", "cpx", "q", "ky", "ru"], [0.15198404474686522, 0.357057116240794, 0.39798339955526973, 0.04963727175712823, 0.0357384491004648, 0.007552977658364964]),
outP{Float64}(20.01, 900.0, 6, -893.3715313045951, ["g", "liq", "cpx", "q", "ru"], [0.41375670086260935, 0.22026152423749337, 0.3207192955527368, 0.0388066946016078, 0.006300512552990564]),
outP{Float64}(20.01, 1000.0, 6, -907.017938947883, ["liq", "g", "cpx", "ru"], [0.3288487888216254, 0.37004133102828596, 0.2989707839457164, 0.002103318761325104]),
outP{Float64}(20.01, 1100.0, 6, -921.4690947815959, ["liq", "cpx", "g"], [0.420477230111506, 0.2769090622269194, 0.30257827581798524]),
outP{Float64}(20.01, 1200.0, 6, -936.7891948466734, ["cpx", "g", "liq"], [0.23078808430016523, 0.16614317601730302, 0.6030391738853933]),
outP{Float64}(20.01, 1300.0, 6, -953.2883351018679, ["cpx", "liq"], [0.05486715065716554, 0.9451462690517387]),
outP{Float64}(20.01, 1400.0, 6, -970.8204430554073, ["liq"], [0.9999971528738053]),
outP{Float64}(25.01, 800.0, 6, -871.5252346540785, ["liq", "g", "cpx", "q", "ky", "ru"], [0.12719541354683653, 0.3769221372846751, 0.3991819016867496, 0.058935649547046845, 0.030097242523053295, 0.007640006580170008]),
outP{Float64}(25.01, 900.0, 6, -884.240331515353, ["g", "cpx", "liq", "q", "ky", "ru"], [0.42127765689261737, 0.3417444492769789, 0.1718420719267391, 0.05298686030904526, 0.00550660670209719, 0.006601026197142296]),
outP{Float64}(25.01, 1000.0, 6, -897.7070717283865, ["g", "liq", "cpx", "q", "ru"], [0.4050874470444323, 0.25152525670393905, 0.31329484928588985, 0.026504333984554186, 0.003528264107579645]),
outP{Float64}(25.01, 1100.0, 6, -911.96476906289, ["cpx", "liq", "g"], [0.2834007764248975, 0.3592026664550679, 0.35735984502122464]),
outP{Float64}(25.01, 1200.0, 6, -927.0146262099383, ["g", "liq", "cpx"], [0.28026425370638836, 0.4776804207531824, 0.24201518721716936]),
outP{Float64}(25.01, 1300.0, 6, -943.0180238271741, ["liq", "g", "cpx"], [0.7306159561196144, 0.11761576976155234, 0.15174442875242725]),
outP{Float64}(25.01, 1400.0, 6, -960.2947844125035, ["liq"], [0.9999943774876113]),
outP{Float64}(30.01, 800.0, 6, -862.6549891242814, ["fl", "g", "cpx", "coe", "ky", "ru"], [0.0752878408649747, 0.40976061677233433, 0.4013777744027197, 0.08361212336017673, 0.021875709083563406, 0.008196489949445185]),
outP{Float64}(30.01, 900.0, 6, -875.2558013512793, ["g", "cpx", "liq", "coe", "ky", "ru"], [0.43459815121293904, 0.3478125964971234, 0.1462877964801376, 0.0622405157704724, 0.0024839372330202835, 0.006541016428426618]),
outP{Float64}(30.01, 1000.0, 6, -888.587343580091, ["g", "cpx", "liq", "q", "ru"], [0.4219532412822655, 0.3287284573369214, 0.20125064501001322, 0.04400715011156917, 0.00401122194828888]),
outP{Float64}(30.01, 1100.0, 6, -902.6578857906828, ["g", "liq", "cpx", "q"], [0.3862764272505425, 0.30174709792920645, 0.3034186295386992, 0.008516476418805194]),
outP{Float64}(30.01, 1200.0, 6, -917.4997995597762, ["g", "liq", "cpx"], [0.3358470488598218, 0.3996636384700852, 0.2644575727332914]),
outP{Float64}(30.01, 1300.0, 6, -933.1625365358786, ["g", "liq", "cpx"], [0.24215863043559246, 0.5640065546295734, 0.19380956988356382]),
outP{Float64}(30.01, 1400.0, 6, -949.9243778546029, ["liq", "g", "cpx"], [0.9228047874816635, 0.04602807369814248, 0.031139419508117463])
]