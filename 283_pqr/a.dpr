procedure TForm1.Button3Click(Sender: TObject);
const target=1000;
var x,k,f:integer;y,sm,k2:integer;z,bm:int64;big,big2,h:int64;maxfactor,minfactor:int64;count,maxf:integer;
divisors:array[0..10000] of integer;
top,curtop,multi,multi2,multi3,i,j,d:integer; fp:int64;
perimeter:int64;
area:extended;
sq12:extended;
smpf:array of integer;
sievemax,siv:integer;
u,v,uf,vf,aux:integer;
s:string;
procedure add(f,multi:integer);
var i,j:integer;h:int64;
begin
   curtop:=top;
   for j:=0 to top do
   begin
      h:=divisors[j];
       for i:=1 to multi do
         begin
            h:=h*f; if h>maxfactor then break;
            inc(curtop);
            divisors[curtop]:=h;
         end;
   end;
top:=curtop;
end;
procedure process(d,m:integer);
begin
   if (m<0) or (d>maxfactor)then exit;
   if d>=minfactor then
   begin
      sm:=d+k2;
      y:=sm div x;
      if sm=x*y then
       begin
         bm:=trunc(big/d)+k2;
         z:=trunc(bm/x);
         if bm=x*z then begin
         inc(count);inc(perimeter,x+y+z);area:=area+k*(x+y+z) end;
        end;
    end;
process(d shl 1,m-1);
end;
begin
starttimer;
  maxfactor:=0;
  perimeter:=0;
  area:=0;
  count:=0;
divisors[0]:=1;
sievemax:=8*target*target;
siv:=4*target;
setlength(smpf,sievemax+1);
for i:=1 to sievemax do
smpf[i]:=2*i+1;
for i:=1 to siv do
begin
j:=i shl 1 ;
  if smpf[i]=j+1 then
    begin
      f:=j+1;
      j:=j*(i+1);
       while j<=sievemax do
       begin
          if smpf[j]>f then smpf[j]:=f;
          inc(j,f);
       end
    end;
end;
 for k:=1 to target do
 begin
 k2:=(k*k) shl 2;
 for x:=1 to trunc(sqrt(12)*k) do
 begin
    multi2:=2;
    u:=k;v:=k2+x*x;
    big:=int64(k2)*v;
    maxfactor:=trunc(sqrt(big+0.0));
     minfactor:=x*x-k2;
    top:=0;
    while u and 1=0 do begin inc(multi2,2);u:=u shr 1;end;
    while v and 1=0 do begin inc(multi2);v:=v shr 1;end;
    uf:=smpf[u shr 1];vf:=smpf[v shr 1];
    while (u>1) and (v>1) do
    begin
       if uf=vf then
       begin
         multi:=3;
         u:=u div uf;
         aux:=u div uf;
         while u-aux*uf=0 do begin inc(multi,2);u:=aux;aux:=u div uf; end;
         v:=v div uf;
         aux:=v div uf;
         while v-aux*uf=0 do begin inc(multi);v:=aux;aux:=v div uf;end;
         add(uf,multi);
         uf:=smpf[u shr 1];vf:=smpf[v shr 1];
       end
       else
       begin
       if (uf<vf) then
       begin
         multi:=2;
         u:=u div uf;
         aux:=u div uf;
         while u-aux*uf=0 do begin inc(multi,2);u:=aux;aux:=u div uf; end;
         add(uf,multi);
         uf:=smpf[u shr 1];
       end
       else
       begin
         multi:=1;
         v:=v div vf;
         aux:=v div vf;
         while v-aux*vf=0 do begin inc(multi);v:=aux;aux:=v div vf;end;
         add(vf,multi);
         vf:=smpf[v shr 1];
       end;
      end;
     end;

while u>1 do
  begin
    multi:=2;
    u:=u div uf;
    aux:=u div uf;
    while u-aux*uf=0 do begin  inc(multi,2);u:=aux;aux:=u div uf; end;
    add(uf,multi);
    uf:=smpf[u shr 1];
  end;

while v>1 do
 begin
    multi:=1;
    v:=v div vf;
    aux:=v div vf;
    while v-aux*vf =0 do begin  inc(multi);v:=aux;aux:=v div vf; end;
    if vf<=maxfactor then add(vf,multi) else break;
    vf:=smpf[v shr 1];
 end;

for i:=0 to top do
  begin
  d:=divisors[i];
  if odd(x) then
  process(d,multi2) else
  process(d shl 1,multi2-1);
  end;

 end;
 end;

stoptimer;
if area<intpower(2,62) then s:=inttostr(trunc(2*area)) else s:=floattostrf(2*area,ffgeneral,18,18);
memo1.lines.add(inttostr(target)+' '+inttostr(count)+' '+inttostr(perimeter*2)+' '+s+' '+elapsedtime);

end;
