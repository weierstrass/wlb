% plot 2D magnitude of vector field

function wlb_plot_magnitude(u, v)
    figure('name','Absolute value of field'); clf;
    uabs = sqrt(u.^2 + v.^2);
    imagesc(uabs')
    axis tight equal
end