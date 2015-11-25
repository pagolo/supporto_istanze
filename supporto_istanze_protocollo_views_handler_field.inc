<?php
class supporto_istanze_protocollo_views_handler_field extends views_handler_field {
  function render($values) {
    static $i = 1;
    $value = $this->get_value($values);
    $sid = $values->webform_submissions_node_sid;
    $uid = $values->users_webform_submissions_uid;
    $tid = $values->webform_submissions_node__supporto_istanze_tid;
    $nodata = is_null($values->webform_submissions_node__supporto_istanze_tid);
    if (user_access('protocollato') && 
      ($nodata || 
        ((property_exists($values, 'webform_submissions_node__supporto_istanze_acquisito_stato') && 
          is_null($values->webform_submissions_node__supporto_istanze_acquisito_stato)) || 
        (property_exists($values, 'webform_submissions_node__supporto_istanze_concedibile_stato') && 
          is_null($values->webform_submissions_node__supporto_istanze_concedibile_stato))))) {
      $ass_array = array();
      $ass_array['my_checkbox'] = drupal_get_form('supporto_istanze_form_'.$i, $sid, $uid, $nodata? 0 : $tid, $nodata? 0 : $value, 'protocollo');
      $html = theme('supporto_istanze_views', array ('content' => '', 'assoc' => $ass_array));
    }
    elseif ($nodata || $value == 0) {
      $html = '---';
    } else {
      $html = '<img src="/sites/all/modules/supporto_istanze/icone/si.png" al="protocollato">'; // sostituire con icona
    }
    ++$i;
    return $html;
  }
}
