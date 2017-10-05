% from Rodrigues vector to Euler angles

function q = ro2eu(r)

q = om2eu(ro2om(r));