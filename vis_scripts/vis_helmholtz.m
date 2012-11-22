%helmholtz vizualisation script

clear all; clc;
path = 'data1/';
u = csvread([path 'rho.csv']);
[ny nx] = size(u);


figure(4); clf;
[X Y] = meshgrid(linspace(0, 1, nx), linspace(0, 1, ny))
surf(X, Y, u);shading interp;
axis tight
lambda = 2.0;

figure(5); clf;
[x y] = meshgrid(linspace(0, 1, nx), linspace(0, 1, ny));
mu = sqrt(lambda^2 + pi^2)
z = cos(pi*x).*sinh(mu*(1-y))/sinh(mu);
surf(z);shading interp;
title('ANA')
axis tight

figure(6); clf;
surf(X, Y, abs(u-z));shading interp;
%title('|u_{chai} - u_{ana}|')
%view([0 ,0, 1]);
axis tight
%colorbar;


err =norm(u-z)