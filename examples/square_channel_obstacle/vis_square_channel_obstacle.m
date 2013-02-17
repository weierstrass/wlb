% Visualization script for the force driven poiseuille benchmark.
%
% Andreas Bülling, 2013
% andreas@bulling.se
%

clc; close all;
addpath('../../vis_scripts')

file = 'u.csv';
[N, ux, uy, uz] = wlb_read_csv_array(file);

size(ux)

A = ux(:, :, 10);
B = uy(:, :, 10);
size(A)

% visualize velocity field.
figure(1)
imagesc(sqrt(A'.^2 + B'.^2))

figure(2)
streamslice( A', B');