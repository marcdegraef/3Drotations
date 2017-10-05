% from axis-angle pair to Euler angles

function q = ax2eu(ax)


q = om2eu(ax2om(ax));