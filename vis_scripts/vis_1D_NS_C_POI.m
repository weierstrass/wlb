%visualization script for 1D poisson-boltzmann eq.

clear all;
clc;

N = 68
% 
 path = ['dataPE' num2str(N) '/rho.csv']
 rho = csvread(path)
% 
% 

%axis equal
figure(99)
surf(rho)
title('psi')
% 
% 
 [ny nx] = size(rho)
% 
% d = 1e-5;
% V0 = 1.0;
% V0_ana = -50e-3;
% 
% figure(4); clf;
% lap = del2(rho);
% plot(-lap(1:floor(ny/2), floor(nx/2)))
% 
% figure(6);clf;
% plot(0:(floor(ny/2)-1), rho(1:floor(ny/2), floor(nx/2))', 'rx')
% 
% 
path2 = ['dataNP' num2str(N) '/'];
Cneg = csvread([path2 'ni_neg.csv'])

figure(7);clf;
plot(1:(floor(ny)-2), Cneg(2:floor(ny-1), floor(nx/2))', 'rx')
title('pos/neg ion concentration')
hold on;
Cpos = csvread([path2 'ni_pos.csv']);



%figure(8);clf;
plot(1:(floor(ny)-2), Cpos(2:floor(ny-1), floor(nx/2))', 'bx')



% figure(8);clf;
% plot(0:(floor(ny/2)-2), Cpos(2:floor(ny/2), floor(nx/2))' - Cneg(2:floor(ny/2), floor(nx/2))', 'bx')
% title('rho_e')
% 

INT_POS = sum(Cpos(:, floor(nx/2)))
INT_NEG = sum(Cneg(:, floor(nx/2)))
MEAN_POS = mean(Cpos(:, floor(nx/2)))
MEAN_NEG = mean(Cneg(:, floor(nx/2)))

% figure(9); clf;
% dpsiy = csvread(['dataPSI' num2str(N) '/dpsiy.csv']);
% dpsiy = dpsiy/V0_ana;
% plot(0:(floor(ny)-1), dpsiy(1:floor(ny), floor(nx/2))', 'gx')
% 
% hold on;
% ana_dpsiy = -(rho(1:floor(ny)-1, floor(nx/2)) - rho(2:floor(ny), floor(nx/2)));
% 
% plot(0.5:(floor(ny)-1.5), ana_dpsiy, 'ro')
% title('green - first moment, red - finite difference')
% 
% figure(33)
% surf(dpsiy)
% 
% figure(44)
% surf(Cpos)
% title('cpos')
% 
% figure(55)
% surf(Cneg)
% title('cneg')
% 
 figure(66)
% 
 path = ['dataNS' num2str(N) '/'];
%path = '29-10-12/dataNS300_075/';

ux = csvread([path 'ux.csv']);
uy = csvread([path 'uy.csv']);

uabs = sqrt(ux.^2 + uy.^2);
%uabs = uabs(2:end-1, :);
surf(uabs)


figure(67); clf;
streamslice(ux, uy, 2)
%axis equal tight
title('u')

figure(68); clf;
C = [linspace(1, 1, 128)' linspace(1, 0, 128)' linspace(1, 0, 128)'];
colormap(C);
imagesc(uabs)
%axis equal tight
title('uabs')

figure(69); clf;
rhoNS = csvread([path 'rho.csv'])
surf(rhoNS)

figure(70); clf;hold on
%analyical solution
yvv = linspace(0 + 0.5/(ny-1), 1 - 0.5/(ny-1), 200);
w = 2/7;
c23 = 1/3;
nu = c23*(1/w - 0.5)
F = 1e-4;

umax = 1/8/nu*F*(((ny-1-1)))^2

poi = umax*(1 - (yvv*2 - 1).^2);
vec = -(0 + 0.5/(ny-1) - yvv).*(1 - 0.5/(ny-1) - yvv);
vec = umax*vec/max(vec);
%plot(yvv, vec, '-r')
hold on

plot(linspace(0 + 1/(ny), 1 - 1/(ny), ny-2), ux(2:ny-1, ceil(nx/2)), '--b')





%force

figure(93);clf;
 path = ['dataFX' num2str(N) '/'];
%path = '29-10-12/dataNS300_075/';

fx = csvread([path 'fx.csv']);
plot(1:ny, fx(:, ceil(nx/2)), 'xb')

sum(fx(:, ceil(nx/2)))

%hold on
%figure(990)
%surf(Cpos)
% k = sqrt(1.18024e12)*d/(ny-1)
% ly = ny;
% lin =  @(x) V0*(exp(k*(ly-x)) + exp(k*x))./(exp(k*ly) + 1);
% yv = linspace(0, floor(ny/2)-1, 100);
% plot(yv, lin(yv), 'r')
% 
% kbT_ze = 0.0235253/V0_ana;
% ana = @(x) 2*kbT_ze*log((1 + exp(-k*x)*tanh(0.25*V0/kbT_ze)) ./ (1 - exp(-k*x)*tanh(0.25*V0/kbT_ze)));
% plot(yv, ana(yv), 'g-')
% 
% figure(7);clf;
% plot(0:(floor(nx/2)-1), rho(floor(ny/2), 1:floor(nx/2))', 'kx')
% hold on;
% 
% kx = sqrt(1.18024e12)*d/nx
% lx = nx;
% linx =  @(x) V0*(exp(kx*(lx-x)) + exp(kx*x))./(exp(kx*lx) + 1);
% xv = linspace(0, floor(nx/2)-1, 100);
% 
% plot(xv, linx(xv), 'k')