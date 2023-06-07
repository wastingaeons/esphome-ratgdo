import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID
from esphome.components import binary_sensor
from .. import ratgdo_ns, register_ratgdo_child, RATGDO_CLIENT_SCHMEA

DEPENDENCIES = ["ratgdo"]

RATGDOBinarySensor = ratgdo_ns.class_(
    "RATGDOBinarySensor", binary_sensor.BinarySensor, cg.Component
)
SensorType = ratgdo_ns.enum("SensorType")

CONF_TYPE = "type"
TYPES = {
    "motion": SensorType.RATGDO_SENSOR_MOTION,
    "obstruction": SensorType.RATGDO_SENSOR_OBSTRUCTION,
}


CONFIG_SCHEMA = (
    binary_sensor.binary_sensor_schema(RATGDOBinarySensor)
    .extend(
        {
            cv.Required(CONF_TYPE): cv.enum(TYPES, lower=True),
        }
    )
    .extend(RATGDO_CLIENT_SCHMEA)
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await binary_sensor.register_binary_sensor(var, config)
    await cg.register_component(var, config)
    cg.add(var.set_binary_sensor_type(config[CONF_TYPE]))
    await register_ratgdo_child(var, config)
