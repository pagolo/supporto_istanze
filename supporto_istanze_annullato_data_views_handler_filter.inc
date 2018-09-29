<?php

/**
 * @file
 * Definition of supporto_istanze_annullato_data_views_handler_filter.
 */

/**
 * Filter handler for annullato_data.
 *
 * @ingroup views_filter_handlers
 */
class supporto_istanze_annullato_data_views_handler_filter extends views_handler_filter_boolean_operator {
  function construct() {
    parent::construct();
    $this->value_value = t('Annullato');
    $this->accept_null = TRUE;
  }
  function get_value_options() {
    $this->value_options = array(1 => t('Annullato'), 0 => t('Non annullato'));
  }
}
