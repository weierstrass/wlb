% Visualization script for the force driven poiseuille benchmark.
%
% Andreas Bülling, 2013
% andreas@bulling.se
%

clc; close all;
addpath('../../vis_scripts')

file = 'u.csv';
[N, ux, uy, ~] = wlb_read_csv_array(file);

% visualize velocity field.
wlb_plot_magnitude(ux, uy);
wlb_plot_streamlines(ux, uy);

% compare with analytical solution 
F = 1e-5;
w = 0.75;
c23 = 1/3;
nu = c23*(1/w - 0.5);

umax = 1/8/nu*F*(((N(2)-1 -1)))^2;
yvv = linspace(0, 1, N(2));

% the bounce-back implementation used gives actual boundary
% half node-node distance into the domain.
vec = -(0  + 0.5/(N(2)-1) -  yvv).*(1 - 0.5/(N(2)-1) -yvv);
vec = umax*vec/max(vec);

figure('name', 'Analytical vs. computed solution'); clf; hold on
plot(vec, 'r')
plot(ux(ceil(N(1)/2), :), 'x')