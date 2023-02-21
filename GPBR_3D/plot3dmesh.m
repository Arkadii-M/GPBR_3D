function plot3dmesh(n_thetha,n_phi,...
  r_approx_str,r_exact_str,mode,...
  output_file)
  ## Create grid
  [thetha,phi]=meshgrid(linspace(0,pi,n_thetha),linspace(0,2*pi,n_phi));
  [xx,yy,zz] = sphere_base(thetha,phi);
  ## Create not visible figure and get handle
  h = figure('visible','off');
##  h = figure();
  ## Parse exact and approx functions and evaluate them
  r_exact = str2func(strcat('@(thetha,phi)',r_exact_str));
  ex_vals = r_exact(thetha,phi);

  r_approx =str2func(strcat('@(thetha,phi)',r_approx_str));
  app_vals = r_approx(thetha,phi);
  ## Print modes:
  ## - both: plot both surfaces
  ## - single: plot only approx surface
  ## - diff: plot the approx surface and color the difference between approx and exact
  if(strcmpi(mode,"both"))
      mesh(ex_vals.*xx,ex_vals.*yy,ex_vals.*zz,"facecolor", "none","edgecolor", "g","linewidth",1.2);
      hold on
      mesh(app_vals.*xx,app_vals.*yy,app_vals.*zz,"facecolor", "none","edgecolor", "b","linewidth",1.2);
      legend("exact","approximate")
    elseif(strcmpi(mode,"single"))
      mesh(app_vals.*xx,app_vals.*yy,app_vals.*zz,"facecolor", "none","edgecolor", "b","linewidth",1.5);
      legend("approximate")
    elseif(strcmpi(mode,"diff"))    
      hold on
      surf(app_vals.*xx,app_vals.*yy,app_vals.*zz,abs(ex_vals.-app_vals))
      colorbar
      colormap("jet")
      legend("approximate (difference)")
  endif
  grid on
  axis equal
  hold off
  view(3)
  print(h,strcat(output_file,'.pdf'),"-dpdfwrite");
endfunction

function [xx,yy,zz]=sphere_base(thetha,phi)
  xx = sin(thetha).*cos(phi);
  yy = sin(thetha).*sin(phi);
  zz = cos(thetha);
endfunction