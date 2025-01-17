# this tests the julia interface to MAGEMin
using Test

cur_dir = pwd();    

if  cur_dir[end-3:end]=="test"
    cd("../")           # change to main directory if we are in /test
end
using MAGEMin_C         # load MAGEMin (needs to be loaded from main directory to pick up correct library in case it is locally compiled)

# Initialize database  - new way
data        =   Initialize_MAGEMin("ig", verbose=true);
test        =   0         #KLB1
data        =   use_predefined_bulk_rock(data, test);

# Call optimization routine for given P & T & bulk_rock
P           =   8.0
T           =   800.0
out         =   point_wise_minimization(P,T, data);

@show out

@test out.G_system ≈ -797.7724719505948
@test out.ph == ["ol", "opx",  "cpx", "spn"]
@test all(abs.(out.ph_frac - [ 0.5856025607115418, 0.23927895188622034, 0.14466038631150246, 0.030458101090737908 ])  .< 1e-2)

# print more detailed info about this point:
print_info(out)
Finalize_MAGEMin(data)


# previous way we defined this (left here for backwards compatibility)
db          = "ig"
gv, z_b, DB, splx_data  = init_MAGEMin(db);
sys_in      =   "mol"     #default is mol, if wt is provided conversion will be done internally (MAGEMin works on mol basis)
test        =   0         #KLB1
gv          =   use_predefined_bulk_rock(gv, test, db);
gv.verbose=-1
P           =   8.0
T           =   800.0
out         =   point_wise_minimization(P,T, gv, z_b, DB, splx_data, sys_in);
@test out.G_system ≈ -797.7724719505948
@test out.ph == ["ol", "opx",  "cpx", "spn"]
@test all(abs.(out.ph_frac - [ 0.5856025607115418, 0.23927895188622034, 0.14466038631150246, 0.030458101090737908 ])  .< 1e-2)
finalize_MAGEMin(gv,DB,z_b)

@testset "pointwise tests  " begin
    n       =   100;
    P       =   fill(8.0,n)
    T       =   fill(800.0,n)
    db      =   "ig" 
    data    =   Initialize_MAGEMin(db, verbose=false);
    out     =   multi_point_minimization(P, T, data, test=0);
    @test out[end].G_system ≈ -797.7724719505948
    @test out[end].ph == ["ol", "opx",  "cpx", "spn"]
    @test all(abs.(out[end].ph_frac - [ 0.5856025607115418, 0.23927895188622034, 0.14466038631150246, 0.030458101090737908 ])  .< 1e-2)

    Finalize_MAGEMin(data)
end

@testset "specify bulk rock" begin
    

    data    = Initialize_MAGEMin("ig", verbose=false);
    
    # One bulk rock for all points
    P,T     = 10.0, 1100.0
    Xoxides = ["SiO2"; "Al2O3"; "CaO"; "MgO"; "FeO"; "Fe2O3"; "K2O"; "Na2O"; "TiO2"; "Cr2O3"; "H2O"];
    X       = [48.43; 15.19; 11.57; 10.13; 6.65; 1.64; 0.59; 1.87; 0.68; 0.0; 3.0];
    sys_in  = "wt"    
    out     = single_point_minimization(P, T, data, X, Xoxides=Xoxides, sys_in=sys_in)

    @test abs(out.G_system + 916.8691829970941)/abs(916.8691829970941) < 2e-4


    # different bulk rock per point
    P       = [10.0, 10.0]
    T       = [1100.0, 1100.0]
    Xoxides = ["SiO2"; "Al2O3"; "CaO"; "MgO"; "FeO"; "Fe2O3"; "K2O"; "Na2O"; "TiO2"; "Cr2O3"; "H2O"];
    X1      = [48.43; 15.19; 11.57; 10.13; 6.65; 1.64; 0.59; 1.87; 0.68; 0.0; 3.0];
    X2      = [49.43; 14.19; 11.57; 10.13; 6.65; 1.64; 0.59; 1.87; 0.68; 0.0; 3.0];
    X       = [X1,X2]
    sys_in  = "wt"    
    out     = multi_point_minimization(P, T, data, X, Xoxides=Xoxides, sys_in=sys_in)
    
    @test out[1].G_system ≈ -916.8691829970941 rtol=2e-4
    @test out[2].G_system ≈ -912.6305628108618 rtol=2e-4

    Finalize_MAGEMin(data)
end

@testset "view array composition" begin

    data    = Initialize_MAGEMin("ig", verbose=false);

    # One bulk rock for all points
    P,T     = 10.0, 1100.0
    Xoxides = ["SiO2"; "Al2O3"; "CaO"; "MgO"; "FeO"; "Fe2O3"; "K2O"; "Na2O"; "TiO2"; "Cr2O3"; "H2O"];
    X       = [48.43; 15.19; 11.57; 10.13; 6.65; 1.64; 0.59; 1.87; 0.68; 0.0; 3.0];
    sys_in  = "wt"

    X = [[1.0], X]
    X_view = @view X[2,:]

    out     = single_point_minimization(P, T, data, X_view, Xoxides=Xoxides, sys_in=sys_in)

    @test abs(out.G_system + 917.008526)/abs(917.008526) < 2e-4

    Finalize_MAGEMin(data)
end

@testset "convert bulk rock" begin

    bulk_in_ox = ["SiO2"; "Al2O3"; "CaO"; "MgO"; "FeO"; "Fe2O3"; "K2O"; "Na2O"; "TiO2"; "Cr2O3"; "H2O"];
    bulk_in    = [48.43; 15.19; 11.57; 10.13; 6.65; 1.64; 0.59; 1.87; 0.68; 0.0; 3.0];
    bulk_rock,ox  = convertBulk4MAGEMin(bulk_in,bulk_in_ox,"wt","ig");

    @test bulk_rock ≈ [46.12597764761598, 8.52489397284109, 11.805554573333653, 14.383528505497756, 6.471419573392541, 0.35839516987780934, 1.7264383468329216, 0.4871154401452383, 0.5876614012114892, 0.0, 9.529015369251512]

    bulk_in_ox = ["SiO2"; "Al2O3"; "CaO"; "MgO"; "FeO"; "Fe2O3"; "K2O"; "Na2O"; "TiO2"; "MnO"; "H2O"];
    bulk_in    = [69.64; 13.76; 1.77; 1.73; 4.32; 0.4; 2.61; 2.41; 0.80; 0.07; 0.0];
    bulk_rock,ox  = convertBulk4MAGEMin(bulk_in,bulk_in_ox,"wt","mp");

    @test bulk_rock ≈ [76.57038397179574, 8.914984523583415, 2.0849576977131403, 2.835783318610597, 4.30275071755529, 1.8302970975627948, 2.568605789798099, 0.6615823604771729, 0.16546809116073818, 0.06518643174302832, 0.0]
end


@testset "test Seismic velocities & modulus" begin
    # Call optimization routine for given P & T & bulk_rock
    data         = Initialize_MAGEMin("ig", verbose=false);
    test        = 0;
    data         = use_predefined_bulk_rock(data, test)
    P           = 8.0
    T           = 1200.0
    out         = point_wise_minimization(P,T, data)

    tol = 1e-2;
    @test abs(out.bulkMod - 95.43250604585427           < tol)

    @test abs(out.shearMod - 30.001704964996087         < tol)
    @test abs(out.Vs - 3.058743757481179                < tol)
    @test abs(out.Vp - 6.498830803546243                < tol)
    @test abs(out.Vs_S - 4.316088476699674              < tol)
    @test abs(out.Vp_S - 7.3995266284026515             < tol)
    @test abs(out.bulkModulus_M - 27.75632909384032     < tol)
    @test abs(out.bulkModulus_S - 95.9877313311181      < tol)
    @test abs(out.shearModulus_S - 59.773652975301474   < tol)

    Finalize_MAGEMin(data)
end

# Stores data of tests
mutable struct outP{ _T  } 
    P           ::  _T
    T           ::  _T 
    test        ::  Int64

    G           ::  _T
    ph          ::  Vector{String}
    ph_frac     ::  Vector{Float64}
end

print_error_msg(i,out) = println("ERROR for point $i with test=$(out.test); P=$(out.P); T=$(out.T); stable phases=$(out.ph), fractions=$(out.ph_frac)")


# Automatic testing of all points
function TestPoints(list, data::MAGEMin_Data)

    # Compute all points
    P = [ l.P for l in list]
    T = [ l.T for l in list]
    test = [ l.test for l in list]
    out_vec = multi_point_minimization(P, T, data, test = test[1]);

    # Check if the points this fit
    for (i,out) in enumerate(out_vec)
        VerifyPoint(out, list[i], i)
    end
    return nothing
end

# This checks whether a single point agrees with precomputed values & prints a message if not
function VerifyPoint(out, list, i)

     # We need to sort the phases (sometimes they are ordered differently)
     ind_sol = sortperm(list.ph)
     ind_out = sortperm(out.ph)
     
     result1 = @test out.G_system  ≈ list.G     rtol=1e-3
     result2 = @test out.ph[ind_out]        == list.ph[ind_sol]
     result3 = @test out.ph_frac[ind_out] ≈ list.ph_frac[ind_sol] atol=5e-2       # ok, this is really large (needs fixing for test6!)
     
     # print more info about the point if one of the tests above fails
     if isa(result1,Test.Fail) || isa(result2,Test.Fail) || isa(result3,Test.Fail)
         print_error_msg(i,list)
     end
     
     return nothing
end

# load reference for built-in tests
println("Testing points from the reference diagrams:")
@testset verbose = true "Total tests" begin

    # Igneous database
    println("  Starting KLB-1 peridotite tests")
    db  = "ig"  # database: ig, igneous (Holland et al., 2018); mp, metapelite (White et al 2014b)
    data = Initialize_MAGEMin(db, verbose=false);
   
    gv.verbose=-1;
    @testset "IG-DB - KLB-1 peridotite" begin
        include("test_diagram_test0.jl")
        TestPoints(list, data)
    end
    Finalize_MAGEMin(data)

    println("  Starting RE-46 icelandic basalt tests")
    db          = "ig"  # database: ig, igneous (Holland et al., 2018); mp, metapelite (White et al 2014b)
    data = Initialize_MAGEMin(db, verbose=false);
    gv.verbose=-1;
    @testset "IG-DB - RE-46 icelandic basalt" begin
        include("test_diagram_test1.jl")
        TestPoints(list, data)
    end
   
    println("  Starting Wet MORB tests")
    db          = "ig"  # database: ig, igneous (Holland et al., 2018); mp, metapelite (White et al 2014b)
    data = Initialize_MAGEMin(db, verbose=false);
    @testset "IG-DB - Wet MORB" begin
        include("test_diagram_test6.jl")
        TestPoints(list, data)
    end
    Finalize_MAGEMin(data)

    # Metapelite database
    println("  Starting WM Pelite tests")
    db  = "mp"  # database: ig, igneous (Holland et al., 2018); mp, metapelite (White et al 2014b)
    data = Initialize_MAGEMin(db, verbose=false);
   
    gv.verbose=-1;
    @testset "MP-DB - WM Pelite" begin
        include("test_diagram_test0_mp.jl")
        TestPoints(list, data)
    end
    Finalize_MAGEMin(data)

    println("  Starting Gt-Migmatite tests")
    db  = "mp"  # database: ig, igneous (Holland et al., 2018); mp, metapelite (White et al 2014b)
    data = Initialize_MAGEMin(db, verbose=false);
   
    gv.verbose=-1;
    @testset "MP-DB - Gt-Migmatite" begin
        include("test_diagram_test4_mp.jl")
        TestPoints(list, data)
    end
    Finalize_MAGEMin(data)

    # Metabasite database
    println("  Starting SQA Amphibole tests")
    db  = "mb"  # database: ig, igneous (Holland et al., 2018); mp, metapelite (White et al 2014b)
    data = Initialize_MAGEMin(db, verbose=false, mbCpx = 1);
   
    gv.verbose=-1;
    @testset "MB-DB - SQA Amphibole" begin
        include("test_diagram_test0_mb.jl")
        TestPoints(list, data)
    end
    Finalize_MAGEMin(data)


end



cd(cur_dir)

