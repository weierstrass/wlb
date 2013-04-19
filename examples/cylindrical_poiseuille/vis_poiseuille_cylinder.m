% Visualization script for the cylindrical poiseuille benchmark.
%
% Andreas Bülling, 2013
% andreas@bulling.se
%

clc; close all;
addpath('../../vis_scripts')

file = 'u.csv';
[N, ux, uy, uz] = wlb_read_csv_array(file);

N
A = squeeze(ux(2, :, :));

% visualize velocity field.
wlb_plot_magnitude(A, zeros(N(2), N(3)));

%compare with analytical solution
figure(2); clf; hold on;
plot(A(:, ceil(N(2)/2)))
y = ceil(N(2)/2)

F = 1e-5;
w = 0.75;
c23 = 1/3;
nu = c23*(1/w - 0.5);

umax = 1/16/nu*F*(((N(2)-1-1)))^2
yvv = linspace(0, 1, N(2));

vec = -(0  + 0.5/(N(2)-1) -  yvv).*(1 - 0.5/(N(2)-1) -yvv);
vec = umax*vec/max(vec);
plot(vec, 'r')

err = umax / A(ceil(N(2)/2), ceil(N(2)/2))