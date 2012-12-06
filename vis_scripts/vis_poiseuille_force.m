%visualization of poiseuille flow
clear all; clc;
path = 'bench_force_poi/';

ux = csvread([path 'ux.csv']);
uy = csvread([path 'uy.csv']);
rho = csvread([path 'rho.csv']);% - csvread([path2 'rho.csv']);
uabs = sqrt(ux.^2 + uy.^2);
uabs(rho < 1e-5) = 0;
ux(uabs < 1e-5) = 0;
uy(uabs < 1e-5) = 0;
[Ny Nx] = size(ux)

figure(2); clf;
streamslice(ux, uy, 2)
axis equal tight
title('u')

figure(44); clf;
surf(ux, uy)

figure(3); clf;
C = [0, 0, 0; jet(1024)];%[linspace(1, 1, 128)' linspace(1, 0, 128)' linspace(1, 0, 128)'];
colormap(C);
imagesc(uabs)
axis equal tight
title('uabs')

figure(4); clf;
imagesc(rho)
axis equal tight
title('rho')

figure(5);clf;
yv = linspace(0 + 1/(Ny-1), 1 - 1/(Ny-1), Ny-2)
%plot([0.5/(Ny-1) yv 1 - 0.5/(Ny-1)], [0; ux(2:Ny-1, ceil(Nx/2)); 0], 'xb')
plot(linspace(0 + 1/(Ny-1), 1 - 1/(Ny-1), Ny-2), ux(2:Ny-1), 'xb')
hold on

%analyical solution
yvv = linspace(0 + 0.5/(Ny-1), 1 - 0.5/(Ny-1), 200);
yvv = linspace(0, 1, 200);
w = 0.75;
c23 = 1/3;
nu = c23*(1/w - 0.5)
F = 1e-4;

umax = 1/8/nu*F*(((Ny-1 -1)))^2

poi = umax*(1 - (yvv*2 - 1).^2);
vec = -(0  + 0.5/(Ny-1) -  yvv).*(1 - 0.5/(Ny-1) -yvv);
vec = umax*vec/max(vec);
plot(yvv, vec, '-r')

figure(6); clf;
plot(linspace(0, 1, Nx), rho(floor(Ny/2), :))
plot(linspace(0 + 1/(Ny-1), 1 - 1/(Ny-1), Ny-2), ux(2:Ny-1, ceil(Nx/2)), 'xb')
%plot(linspace(0, 1, Ny), ux, 'xb')

yvv = linspace(0 + 1/(Ny-1), 1 - 1/(Ny-1), Ny-2);
vec = -(0  + 0.5/(Ny-1) -  yvv).*(1 - 0.5/(Ny-1) -yvv);
vec = umax*vec/max(vec);
err = sqrt(mean((ux(2:Ny-1) - vec).^2))
maxerr = max(abs((ux(2:Ny-1) - vec)))
plot(err)