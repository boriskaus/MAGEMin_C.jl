# MAGEMin_C.jl


> [!CAUTION]
> This is the local development version of MAGEMin_C by Boris. Most users are probably only interested in officially the released version of the code, which you can find [here](https://github.com/ComputationalThermodynamics/MAGEMin_C.jl) instead.  


## Using the julia interface
First install julia. We recommend downloading the official binary from the [julia](julialang.org) webpage.

Next, install the `MAGEMin_C` package with:
```julia
julia> ]
pkg> add https://github.com/boriskaus/MAGEMin_C.jl
```
You can check if it works on your system by running the build-in test suite:
```julia
pkg> test MAGEMin_C
```

> [!WARNING]
> As this is the development version, not all tests will pass. 

By pushing `backspace` you return from the package manager to the main julia terminal. This will download a compiled version of the library as well as some wrapper functions to your system.

Next, you can do calculations with:
### Example 1 - predefined compositions
This is an example of how to use it for a predefined bulk rock composition:
```julia
julia> using MAGEMin_C
julia> db   = "ig"  # database: ig, igneous (Holland et al., 2018); mp, metapelite (White et al 2014b)
julia> data = Initialize_MAGEMin(db, verbose=true);
julia> test = 0         #KLB1
julia> data = use_predefined_bulk_rock(data, test);
julia> P    = 8.0;
julia> T    = 800.0;
julia> out  = point_wise_minimization(P,T, data);
 Status             :            0 
 Mass residual      : +7.81220e-06
 Rank               :            0 
 Point              :            1 
 Temperature        :   +800.00000       [C] 
 Pressure           :     +8.00000       [kbar]

 SOL = [G: -797.772] (26 iterations, 40.51 ms)
 GAM = [-979.332401,-1774.517815,-795.446831,-673.822884,-375.051876,-920.382309,-830.531600,-1027.480560,-258.780857,-1330.110569]

 Phase :      opx       ol      cpx      spn 
 Mode  :  0.23894  0.58430  0.14500  0.03176 
```

### Example 2 - custom composition
And here a case in which you specify your own bulk rock composition.
```julia
julia> using MAGEMin_C
julia> data    = Initialize_MAGEMin("ig", verbose=false);
julia> P,T     = 10.0, 1100.0
julia> Xoxides = ["SiO2"; "Al2O3"; "CaO"; "MgO"; "FeO"; "Fe2O3"; "K2O"; "Na2O"; "TiO2"; "Cr2O3"; "H2O"];
julia> X       = [48.43; 15.19; 11.57; 10.13; 6.65; 1.64; 0.59; 1.87; 0.68; 0.0; 3.0];
julia> sys_in  = "wt"
julia> out     = single_point_minimization(P, T, data, X=X, Xoxides=Xoxides, sys_in=sys_in)
Pressure          : 10.0      [kbar]
Temperature       : 1100.0    [Celcius]
     Stable phase | Fraction (mol 1 atom basis) 
              opx   0.01905 
              cpx   0.22844 
              liq   0.75253 
     Stable phase | Fraction (wt fraction) 
              opx   0.02015 
              cpx   0.24913 
              liq   0.73077 
Gibbs free energy : -916.867769  (34 iterations; 54.57 ms)
Oxygen fugacity          : 6.690998144597181e-9
```

After the calculation is finished, the structure `out` holds all the information about the stable assemblage, including seismic velocities, melt content, melt chemistry, densities etc.
You can show a full overview of that with
```julia
julia> print_info(out)
```
If you are interested in the density or seismic velocity at the point, access it with
```julia
julia> out.rho
3144.282577840362
julia> out.Vp
5.919986959559542
```
Once you are done with all calculations, release the memory with
```julia
julia> Finalize_MAGEMin(data)
```

### Example 3 - many points
```julia
julia> using MAGEMin_C
julia> db   = "ig"  # database: ig, igneous (Holland et al., 2018); mp, metapelite (White et al 2014b)
julia> data  = Initialize_MAGEMin(db, verbose=false);
julia> test = 0         #KLB1
julia> n    = 1000
julia> P    = rand(8.0:40,n);
julia> T    = rand(800.0:2000.0, n);
julia> out  = multi_point_minimization(P,T, data, test=test);
julia> Finalize_MAGEMin(data)
```
By default, this will show a progressbar (which you can deactivate with the `progressbar=false` option).

You can also specify a custom bulk rock for all points (see above), or a custom bulk rock for every point.



### Running it in parallel
Julia can be run in parallel using multi-threading. To take advantage of this, you need to start julia from the terminal with:
```bash
$julia -t auto
```
which will automatically use all threads on your machine. Alternatively, use `julia -t 4` to start it on 4 threads.
If you are interested to see what you can do on your machine, type:
```julia
julia> versioninfo()
Julia Version 1.9.0
Commit 8e630552924 (2023-05-07 11:25 UTC)
Platform Info:
  OS: macOS (arm64-apple-darwin22.4.0)
  CPU: 12 × Apple M2 Max
  WORD_SIZE: 64
  LIBM: libopenlibm
  LLVM: libLLVM-14.0.6 (ORCJIT, apple-m1)
  Threads: 8 on 8 virtual cores
```
The function `multi_point_minimization` will automatically utilize parallelization if you run it on >1 threads.
