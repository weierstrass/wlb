%visualization script for 1D poisson-boltzmann eq.

clear all;
clc;

N = 12

sd = 0;
 
path = ['dataPE' num2str(N) '/rho.csv']
rho = csvread(path);
[ny nx] = size(rho)

start = (nx-1 - sd)/2+1;

axis equal
figure(99)
% C = [[0 0 0 ]; jet(256)];
% colormap(C);
%rho(start:start+sd, start:start+sd) = 0;
surf([rho])
title('psi')

%C
path2 = ['dataNP' num2str(N) '/'];
Cneg = csvread([path2 'ni_neg.csv']);
%Cneg = Cneg(2:ny-1, :);
Cpos = csvread([path2 'ni_pos.csv']);
%Cpos = Cpos(2:ny-1, :);

figure(44); clf
imagesc(Cpos)
title('cpos')

figure(55); clf
imagesc(Cneg)
title('cneg')

%potential gradient y
% dpsiy = csvread(['dataPSI' num2str(N) '/dpsiy.csv']);
% 
% figure(33)
% surf(dpsiy)
% title('dPSIY')
% 
%velocity field 
path = ['dataNS' num2str(N) '/'];

ux = csvread([path 'ux.csv']);
ux = ux(2:ny-1, :);
uy = csvread([path 'uy.csv']);
%ux(start:start+sd, start:start+sd) = 0;
%uy(start:start+sd, start:start+sd) = 0;
uy = uy(2:ny-1, :);

 figure(66)
 uabs = sqrt(ux.^2 + uy.^2);
 imagesc(uabs)
 title('|u|')


figure(67); clf;
streamslice([ux], [uy], 5)
%streamslice([ux ux], [uy uy], 12)
axis equal tight
title('u charged')

%density
% figure(69); clf;
% rhoNS = csvread([path 'rho.csv']);
% imagesc(rhoNS(2:ny-1, :))
% title('density')

%force
% figure(93);clf;
%  path = ['dataFX' num2str(N) '/'];
% 
% fx = csvread([path 'fx.csv']);
% surf(fx)
% title('fx')
