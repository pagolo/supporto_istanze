<?php
class supporto_istanze_modifica_views_handler_field extends views_handler_field {
  function pre_query() {
    $this->view->si_editable = TRUE;
  }
  /**
   * {@inheritdoc}
   *
   * Perform any database or cache data retrieval here. In this example there is
   * none.
   */
  function query() {
 
  }
 
  /**
   * {@inheritdoc}
   *
   * Modify any end user views settings here. Debug $options to view the field
   * settings you can change.
   */
  function option_definition() {
    $options = parent::option_definition();
    return $options;
  }
 
  /**
   * {@inheritdoc}
   *
   * Make changes to the field settings form seen by the end user when adding
   * your field.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
  }
 
  /**
   * Render callback handler.
   *
   * Return the markup that will appear in the rendered field.
   */
  function render($values) {
    return 'Modifica abilitata';
  }
}
