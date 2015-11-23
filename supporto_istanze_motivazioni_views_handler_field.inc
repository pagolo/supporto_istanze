<?php
class supporto_istanze_motivazioni_views_handler_field extends views_handler_field {
  function render($values) {
    $value = $this->get_value($values);
    return $value . '!';
  }
}
