% read csv data

function [N X Y Z U V W] = wlb_read_csv(file)
    data = csvread(file, 1, 0);
    X = data(:, 1) + 1; %convert to matlab indexing
    Y = data(:, 2) + 1;
    Z = data(:, 3) + 1;
    U = data(:, 4);
    V = data(:, 5);
    W = data(:, 6);
    N = [max(X), max(Y), max(Z)];
end
