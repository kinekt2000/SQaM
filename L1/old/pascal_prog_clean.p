program trap2;


const tol = 1.0E-6;
var sum,upper,lower: real;

function fx(x: real): real;
begin
  fx:=1.0/ sqrt(x)
end;

procedure trapez(lower,upper,tol: real; var sum: real);
var pieces, i: integer;
    x, delta_x, end_sum, mid_sum, sum1: real;
begin
  pieces:=1;
  delta_x:=(upper-lower)/pieces;
  end_sum:=fx(lower)+fx(upper);
  sum:=end_sum*delta_x/2.0;
  mid_sum:=0.0;
  repeat
    pieces:=pieces*2;
    sum1:=sum;
    delta_x:=(upper-lower)/pieces;
    for i:=1 to pieces div 2 do
    begin
      x:=lower+delta_x*(2.0*i-1.0);
      mid_sum:=mid_sum+fx(x)
    end;
  sum:=(end_sum+2.0*mid_sum)*delta_x*0.5;
  until abs(sum-sum1)<=abs(tol*sum)
end;


begin
  lower:=1.0;
  upper:=9.0;
  writeln;
  trapez(lower,upper,tol,sum);
  writeln;
  writeln(chr(7),'area=',sum)
end.
