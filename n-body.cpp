#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>

const double G = 6.674e-11;
const double SOFTENING = 1e-9;

struct Particle {
    double mass;
    double x, y, z;
    double vx, vy, vz;
    double fx, fy, fz;
};

void reset_forces(std::vector<Particle>& particles) {
    for (auto& p : particles) {
        p.fx = p.fy = p.fz = 0.0;
    }
}

void compute_forces(std::vector<Particle>& particles) {
    for (size_t i = 0; i < particles.size(); ++i) {
        for (size_t j = 0; j < particles.size(); ++j) {
            if (i == j) continue;
            double dx = particles[j].x - particles[i].x;
            double dy = particles[j].y - particles[i].y;
            double dz = particles[j].z - particles[i].z;
            double dist_sq = dx * dx + dy * dy + dz * dz + SOFTENING;
            double dist = std::sqrt(dist_sq);
            double force = G * particles[i].mass * particles[j].mass / dist_sq;
            double fx = force * dx / dist;
            double fy = force * dy / dist;
            double fz = force * dz / dist;
            particles[i].fx += fx;
            particles[i].fy += fy;
            particles[i].fz += fz;
        }
    }
}

void update_positions(std::vector<Particle>& particles, double dt) {
    for (auto& p : particles) {
        double ax = p.fx / p.mass;
        double ay = p.fy / p.mass;
        double az = p.fz / p.mass;
        p.vx += ax * dt;
        p.vy += ay * dt;
        p.vz += az * dt;
        p.x += p.vx * dt;
        p.y += p.vy * dt;
        p.z += p.vz * dt;
    }
}

void output_state(const std::vector<Particle>& particles, std::ofstream& out) {
    out << particles.size();
    for (const auto& p : particles) {
        out << '\t' << p.mass << '\t' << p.x << '\t' << p.y << '\t' << p.z
            << '\t' << p.vx << '\t' << p.vy << '\t' << p.vz
            << '\t' << p.fx << '\t' << p.fy << '\t' << p.fz;
    }
    out << '\n';
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " <num_particles> <dt> <steps> <output_interval>\n";
        return 1;
    }

    int num_particles = std::atoi(argv[1]);
    double dt = std::atof(argv[2]);
    int steps = std::atoi(argv[3]);
    int output_interval = std::atoi(argv[4]);

    std::vector<Particle> particles(num_particles);
    for (auto& p : particles) {
        p.mass = 1.0 + std::rand() % 100;
        p.x = std::rand() % 1000;
        p.y = std::rand() % 1000;
        p.z = std::rand() % 1000;
        p.vx = p.vy = p.vz = 0.0;
    }

    std::ofstream out("output.tsv");

    for (int step = 0; step < steps; ++step) {
        reset_forces(particles);
        compute_forces(particles);
        update_positions(particles, dt);
        if (step % output_interval == 0) {
            output_state(particles, out);
        }
    }

    out.close();
    return 0;
}
