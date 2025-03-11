# N-Body Simulation

## Compilation
To compile the project, run the following command in the terminal:

```
make
```

## Usage
Run the simulation with the following syntax:

```
./nbody <num_particles> <dt> <steps> <output_interval>
```

- `num_particles`: Number of particles to simulate
- `dt`: Time step size
- `steps`: Number of iterations (time steps)
- `output_interval`: How often to dump the state to the output file

Example:

```
./nbody 100 1 10000 100
```

## Output
The simulation writes the state of the particles to `output.tsv`.

## Benchmark Tests
Run the following benchmarks to measure performance:

1. Solar system simulation:
```
./nbody 10 200 5000000 10000
```

2. 100 particles, small time step:
```
./nbody 100 1 10000 100
```

3. 1000 particles, small time step:
```
./nbody 1000 1 10000 100
```

## Visualization
Once the simulation completes, you can visualize the output using the provided `plot.py` script:

```
python3 plot.py output.tsv output.pdf 10000
```

