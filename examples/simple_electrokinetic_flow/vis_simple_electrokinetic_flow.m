% vis script for simple electrokinetic888

clc; close all;
addpath('../../vis_scripts')

N = 3974;

file = ['vis_scripts/dataNS' num2str(N) '/u.csv'];
[DIM, ux, uy, uz] = wlb_read_csv_array(file);

A = squeeze(ux(2, :, :));

% visualize velocity field.
wlb_plot_magnitude(ux, uy);
wlb_plot_streamlines(ux, uy);

figure(23); hold on;
plot(ux(2, :));

file = ['u_0/dataNS' num2str(808) '/u.csv']
[DIM, ux, uy, uz] = wlb_read_csv_array(file);
%plot(ux(2, :), 'k');

path = ['vis_scripts/dataNP' num2str(N) '/']
Cpos = csvread([path 'ni_pos.csv']);
Cneg = csvread([path 'ni_neg.csv']);

figure(44); clf
hold on;
plot(Cpos(:, 2))
hold on;
plot(Cneg(:, 2), 'r')
INT_pos = sum(Cpos(:, 2))
title('c_{pos} (b) and c_{neg} (r)')

figure(93);clf;
 path = ['vis_scripts/dataFX' num2str(N) '/'];

fx = csvread([path 'fx.csv']);
surf(fx)
title('fx')

path = ['vis_scripts/dataPE' num2str(N) '/rho.csv']
rho = csvread(path);

axis equal
figure(99)

surf([rho])
title('psi')