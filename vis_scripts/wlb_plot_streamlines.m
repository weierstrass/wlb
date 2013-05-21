% plot 2D magnitude of vector field

function wlb_plot_streamlines(u, v)
    figure('name','Field stream lines'); clf;
    streamslice(u', v')
    %axis equal tight
end