
function plotProperties()
set(gcf,'Position', [0,0,800,400])
set(gca,'FontSize',14)
set(gca, 'FontName', 'Times New Roman');
set(gca,'box','on');
set(0,'defaultlinelinewidth',0.5) 
set(get(gca, 'xlabel'), 'interpreter', 'latex');
set(get(gca, 'xlabel'), 'FontName', 'Times New Roman');
set(get(gca, 'xlabel'), 'FontSize', 14);
set(get(gca, 'ylabel'), 'interpreter', 'latex');
set(get(gca, 'ylabel'), 'FontName', 'Times New Roman');
set(get(gca, 'ylabel'), 'FontSize', 14);
set(legend(), 'interpreter', 'latex');
set(legend(), 'FontName', 'Times New Roman');
set(legend(), 'FontSize', 14);
legend boxoff;
set(gcf, 'WindowStyle', 'normal');
end