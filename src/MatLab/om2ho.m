% from rotation matrix to homochoric

function q = om2ho(om)

q = ax2ho(om2ax(om));