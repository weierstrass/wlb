% read csv data into 3D arrays

function [N U V W] = wlb_read_csv_array(file)
    [N X Y Z Ut Vt Wt] = wlb_read_csv(file); 
    U = zeros(N);
    V = zeros(N);
    W = zeros(N);
    
    %rewrite this part with matrix syntax
    for i=1:N(1)
        for j=1:N(2)
            for k=1:N(3)  
               U(i, j, k) = Ut(sub2ind(N, i, j, k));
               V(i, j, k) = Vt(sub2ind(N, i, j, k));
               W(i, j, k) = Wt(sub2ind(N, i, j, k));
            end
        end
    end
end