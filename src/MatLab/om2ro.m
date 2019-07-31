% from rotation matrix to Rodrigues vectors

function q = om2ro(om)

q = eu2ro(om2eu(om));